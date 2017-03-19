#! /bin/bash

export CHIP=msp430g2553
export DRE_OPTS="-search=random-state -entry-point=main -start-fn=main -target-fn=assert -mmodel=symbolic -imodel=cpuoff"
../run.sh $1
