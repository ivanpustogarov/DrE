#!/usr/bin/python
import sys
import subprocess
import os

if __name__ == "__main__":
	model_dir = sys.argv[1]
	if len(sys.argv) > 2:
		target = sys.argv[2]
	else:
		target = "all"
	chips = os.listdir(model_dir)
	for chip in chips:
		if not chip.startswith("msp430"):
			continue
		if chip.startswith("msp430mcu"):
			continue
		result = subprocess.call(["make", "-C", chip, target])
		if result != 0:
			print "FAIL on chip", chip
			sys.exit(result)
