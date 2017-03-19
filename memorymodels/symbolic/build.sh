#! /bin/bash

FOLDERS=$(find . -maxdepth 1 -type d -iname 'msp*')

for name in $FOLDERS
do 
  cd $name
  make $1
  if [ ! $? -eq 0 ]
  then
    echo "[-] Error while building memory models (see make's output above for specific errors)"
    exit 1
  fi
  cd ../
done
