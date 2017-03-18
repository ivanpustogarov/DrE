#! /bin/bash

CHIP=msp430g2553

DRE_ROOT=../../
DRE=$DRE_ROOT/Release+Asserts/bin/klee
DRE_OPTS="-search=random-state -entry-point=main -start-fn=main -target-fn=assert -mmodel=symbolic -imodel=cpuoff -plugpath=$DRE_ROOT -chip=$CHIP"

if [ "$#" -ne 1 ]; then
  echo "Usage: $0 <file>.bc "
  exit 0
fi

time $DRE $DRE_OPTS $1
