#! /bin/bash

export CHIP=msp430g2553
export DRE_OPTS=" -search=bfs -entry-point=main -start-fn=main -target-fn=assert -mmodel=symbolic -imodel=cpuoff -search=random-state -smmry-break-on-firstfit=0 -smmries-per-run=10"
../run.sh $1
