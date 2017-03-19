#! /bin/bash

export CHIP=msp430g2553
export DRE_OPTS="-entry-point=main -start-fn=main -target-fn=assert -mmodel=symbolic -imodel=cpuoff -search=SD -search=random-state"
../run.sh $1
