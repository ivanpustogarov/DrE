#! /bin/bash

PLUG_PATH=$HOME/Workspaces/DrE

if [ "$#" -ne 1 ]; then
  echo "Usage: $0 <file>.bc "
  exit 0
fi

time ~/Workspaces/DrE/Release+Asserts/bin/klee -search=random-state -entry-point=main -start-fn=main -target-fn=assert -mmodel=symbolic -imodel=cpuoff -plugpath=$PLUG_PATH -chip=msp430g2553 $1
