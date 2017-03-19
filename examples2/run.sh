#! /bin/bash

# This script is not supposed to be invoked directly,
# Use scripts inside specific example folders instead,
# where CIP and DRE_OPTS varaibles are defined.

if [ -z $CHIP ]
then
  echo "Go inside a specific example folder an execute 'run-dre.sh'"
  exit 1
fi

DRE_ROOT=../../
DRE=$DRE_ROOT/Release+Asserts/bin/klee
#DRE_OPTS="-search=random-state -entry-point=main -start-fn=main -target-fn=assert -mmodel=symbolic -imodel=cpuoff -plugpath=$DRE_ROOT -chip=$CHIP"

if [ "$#" -ne 1 ]; then
  echo "Usage: $0 <file>.bc "
  exit 0
fi

time $DRE $DRE_OPTS -plugpath=$DRE_ROOT -chip=$CHIP $1
