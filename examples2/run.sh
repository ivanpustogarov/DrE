#! /bin/bash

if [ -z CHIP ]
then
  echo "Go inside a folder an execute 'run-dre.sh'"
  exit 1
fi

DRE_ROOT=../../
DRE=$DRE_ROOT/Release+Asserts/bin/klee
DRE_OPTS="-search=random-state -entry-point=main -start-fn=main -target-fn=assert -mmodel=symbolic -imodel=cpuoff -plugpath=$DRE_ROOT -chip=$CHIP"
echo "DRE_OPTS=$DRE_OPTS"

if [ "$#" -ne 1 ]; then
  echo "Usage: $0 <file>.bc "
  exit 0
fi

time $DRE $DRE_OPTS $1
