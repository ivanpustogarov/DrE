DrE: DiRected Compositional Symbolic Executor for MSP430 (KLEE-based)
=============================

DrE is an early research prototype and work in progress.

Key features: 

  * Is able to analyse code written for MSP430 family of microcontrollers
  * MSP430 Interrupt and memory models
  * Compositional: it can execute function in isolation and 
    build function summaries.
  * Directed: It tries to find execution paths toward the target line.
    It has two modes of operation: 1) "Forward mode" which prefers shortest
    paths in ICFG toward the target line;
    2) Compositional mode in which tries to smartly combine function
    summaries.

## About Directed Symbolic Execution
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
Compiling DrE is simimlar to compiling KLEE. Here is a summary.

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
CC=gcc CXX=g++ ./configure --with-uclibc=/home/ivan/Workspaces/klee-uclibc --with-llvm=/home/ivan/Workspaces/llvm-3.4 --enable-posix-runtime
```

## Compile instructions 
Check folder examples2.
Let's look at toy-example1:

```C
#include <msp430.h>

#define AVG_LEN (64)
#define AVG_MASK (AVG_LEN - 1)
int avg_buf[AVG_LEN] = {0};

int diff = 0;

int printGesture(int gesture1, int gesture2);
int classify_subgesture(int a);
int avg(int);

int printGesture(int gesture1, int gesture2)
{
  int a = 0;
  if ((gesture1 == 1) && (gesture2 == 2))
  {
    assert(0);
    a = 1;
  }
  else if ((gesture1 == 2) && (gesture2 == 3))
  {
    a = 2;
  }
  return 0;
}

int classify_subgesture(int a)
{
  return a;
}

//#define AVG_LEN (64)
//#define AVG_MASK (AVG_LEN - 1)
int avg(int newVal) {
  //static int avg_buf[AVG_LEN] = {0};
  static int index = 0;
  static int sum = 0;  // TODO: change to 16 bits?
  sum -= avg_buf[index & AVG_MASK];
  sum += avg_buf[index++ & AVG_MASK] = newVal;
  return sum / AVG_LEN;    // TODO: Check ASM to make sure it's a shift.
}

int getGesture()
{
  int a = 1;
  __bis_SR_register(CPUOFF + GIE);        // LPM0, ADC10_ISR will force exit
  if(diff == 1)
  {
    __bis_SR_register(CPUOFF + GIE);        // LPM0, ADC10_ISR will force exit
    if(diff == 3)
    {
      int res1 = classify_subgesture(a);
      return res1;
    }
    else
    {
      int res2 = classify_subgesture(a+1);
      return res2;
    }
  }
  int res3 = classify_subgesture(a+2);
  return res3;
}

//int main(int argc, char *argv[])
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



## About KLEE
`KLEE` is a symbolic virtual machine built on top of the LLVM compiler
infrastructure. Currently, there are two primary components:

  1. The core symbolic virtual machine engine; this is responsible for
     executing LLVM bitcode modules with support for symbolic
     values. This is comprised of the code in lib/.

  2. A POSIX/Linux emulation layer oriented towards supporting uClibc,
     with additional support for making parts of the operating system
     environment symbolic.

Additionally, there is a simple library for replaying computed inputs
on native code (for closed programs). There is also a more complicated
infrastructure for replaying the inputs generated for the POSIX/Linux
emulation layer, which handles running native programs in an
environment that matches a computed test input, including setting up
files, pipes, environment variables, and passing command line
arguments.

Coverage information can be found [here](http://vm-klee.doc.ic.ac.uk:55555/index.html).

For further information, see the [webpage](http://klee.github.io/).
