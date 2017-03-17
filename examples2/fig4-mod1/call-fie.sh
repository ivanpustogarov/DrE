#! /bin/bash

RUNTIME=360000 # seconds
#MAXMEMORY=20000 # in MB
MAXMEMORY=0 # Disable default memory cap of 2000
SYMBEX=fie

echo -e "\n\nWARNING: STDOUT will go to /dev/null"
echo -n "Going to run $SYMBEX for $RUNTIME seconds with memory cap of $MAXMEMORY MB. [Y/n]? "
read yn
if [ $yn == "Y" ]
then
  #time $SYMBEX -plugpath=/home/ivan/Workspaces/fie -imodel=bbl/ -mmodel=symbolic/ -max-memory=$MAXMEMORY -max-time=$RUNTIME -isr-frequency=BBLFreq -search=nurs:covnew all.bc 1>/dev/null
  time $SYMBEX -plugpath=/home/ivan/Workspaces/fie -imodel=bbl/ -mmodel=symbolic/ -max-memory=$MAXMEMORY -max-time=$RUNTIME -isr-frequency=BBLFreq all.bc 1>/dev/null
else
  echo "Cancelled. Bye!"
fi
