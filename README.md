DrE: DiRected compositional symbolic Executor for MSP430 (KLEE-based)
=============================

DrE is an early research prototype and work in progress.

Key features: 

  * Is able to analyse code written for MSP430 family of microcontrollers
  * MSP430 Interrupt and memory models (e.g it supports reads from ADC and other peripherals)
  * Compositional: it can execute functions in isolation and 
    collect execution paths.
  * Directed: It tries to find execution paths toward the target line.
    It has two modes of operation: 1) "Forward mode" which prefers shortest
    paths in ICFG toward the target line;
    2) Compositional mode in which it tries to smartly combine (or stitch) function
    summaries by progapagating relevant constrainst.

## About Directed Symbolic Execution and DrE
Instead of attempting to explore all code paths, directed symbolic
execution starts with a target, i.e., a particular point of interest in
the program.  The output of a successful directed symbolic execution is
a path, defined as a set of constraints on inputs (i.e., sensor
readings) that, if satisfied, will drive the program to the designated
point.

DrE compositional mode uses a modular strategy to efficiently
find paths to program points of interest.  It uses a combination of call
graph and control flow graph analysis with compositional symbolic
execution.  DrE starts by finding possible call chains from the
program's entry point to the function containing the target line.  It
then symbolically executes the function containing the target point and
proceeds through a call chain backwards.  Each function along the way is
(symbolically) executed independently.  To generate inter-procedural
path constraints, DrE then stitches together the execution paths of
individual functions.  To do this, DrE collects, rewrites, and
propagates the relevant constraints and performs a forward pass to check
them.

For efficiency, DrE employs several additional heuristics. DrE biases
state selection towards shorter paths leading to the target program
point and employs a state-pruning strategy to break out of infinite wait
loops.

## Compile instructions 
Compiling DrE is simimlar to compiling KLEE (http://klee.github.io/build-llvm34/).
Here is a short summary.

```
sudo apt-get install build-essential curl libcap-dev git cmake libncurses5-dev python-minimal python-pip unzip
```

First download and compile llvm-3.4 and clang-3.4 (please don't use your
distribution's version)..

```
$ wget http://releases.llvm.org/3.4/llvm-3.4.src.tar.gz
$ tar -xzf llvm-3.4.src.tar.gz
$ cd llvm-3.4/tools
$ wget http://releases.llvm.org/3.4/clang-3.4.src.tar.gz
$ tar -xzf clang-3.4
$ mv clang-3.4 clang
$ cd ../
$ ./configure
$ make (will take a while)
```

Build/Install STP

```
http://klee.github.io/build-stp/
```

Build DrE

```
$ CC=gcc CXX=g++ ./configure --with-llvm=/path/to/llvm-3.4
$ make
```

Build interrupt/memory models, set path to llvm-3.4
```
$ export LLVM_ROOT=/path/to/llvm-3.4
$ cd interrupts
$ make && cd ../
$ cd memorymodels
$ make

```

## Example
Don't forget to set ``LLVM_ROOT`` environment variable.

Consider examples2/toy-example1.c (see below).
It uses peripheral-related memory locations (e.g. `ADC10MEM`),
and interrupts. DrE is able to handle both.

Compile this example as follows (use clang from llvm-3.4):

```
$ cd examples2/toy-example1
$ make
$ ./run-dre.sh main.bc
```
This should find path constraint necessary to reach call to assert() function.
It will generate lots of debug output with the following lines at the end (which is the path constraints):

```
BINGO! Here is are the constraints in KQUERY format:
State: 0x2511000; constraints:
array ADC10MEM_arr1[16] : w32 -> w8 = symbolic
array ADC10MEM_arr2[16] : w32 -> w8 = symbolic
array ADC10MEM_arr3[16] : w32 -> w8 = symbolic
array ADC10MEM_arr4[16] : w32 -> w8 = symbolic
(query [(Eq 1
             (ReadLSB w16 0 ADC10MEM_arr1))
         (Eq 3
             (ReadLSB w16 0 ADC10MEM_arr2))
         (Eq 1
             (ReadLSB w16 0 ADC10MEM_arr3))
         (Eq false
             (Eq 3
                 (ReadLSB w16 0 ADC10MEM_arr4)))]
        false)

And here is are the constraints in SMTLIB2 format:
(set-logic QF_AUFBV )
(declare-fun ADC10MEM_arr1 () (Array (_ BitVec 32) (_ BitVec 8) ) )
(declare-fun ADC10MEM_arr2 () (Array (_ BitVec 32) (_ BitVec 8) ) )
(declare-fun ADC10MEM_arr3 () (Array (_ BitVec 32) (_ BitVec 8) ) )
(declare-fun ADC10MEM_arr4 () (Array (_ BitVec 32) (_ BitVec 8) ) )
(assert (and  (and  (and  (=  (_ bv1 16) (concat  (select  ADC10MEM_arr1 (_ bv1 32) ) (select  ADC10MEM_arr1 (_ bv0 32) ) ) ) (=  (_ bv3 16) (concat  (select  ADC10MEM_arr2 (_ bv1 32) ) (select  ADC10MEM_arr2 (_ bv0 32) ) ) ) ) (=  (_ bv1 16) (concat  (select  ADC10MEM_arr3 (_ bv1 32) ) (select  ADC10MEM_arr3 (_ bv0 32) ) ) ) ) (=  false (=  (_ bv3 16) (concat  (select  ADC10MEM_arr4 (_ bv1 32) ) (select  ADC10MEM_arr4 (_ bv0 32) ) ) ) ) ) )
(check-sat)
(exit)
```


```C

---> toy-example1.c

#include <msp430.h>

...

int main()
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  ADC10CTL0 = ADC10SHT_2 + ADC10ON + ADC10IE; // ADC10ON, interrupt enabled
  ADC10CTL1 = INCH_1;                       // input A1
  ADC10AE0 |= 0x02;                         // PA.1 ADC option select
  P1DIR |= 0x01;                            // Set P1.0 to output direction
  int gesture1 = getGesture();
  int gesture2 = getGesture();

  if((gesture1 == 0) || (gesture2 == 10))
    return 1;
  printGesture(gesture1, gesture2);
  return 2;
}

// ADC10 interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(ADC10_VECTOR))) ADC10_ISR (void)
#else
#error Compiler not supported!
#endif
{
  diff = ADC10MEM;
  __bic_SR_register_on_exit(CPUOFF);        // Clear CPUOFF bit from 0(SR)
}
```
