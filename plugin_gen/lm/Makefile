all:
	clang -ccc-host-triple msp430-elf -c -emit-llvm -I/scratch/davidson/embedded/analysis/model/common -I/scratch/davidson/embedded/analysis/model/include -include/scratch/davidson/embedded/analysis/model/common/isr_compat.h -include/scratch/davidson/embedded/analysis/model/common/msp430.h -D__MSP430__=1 -Wmain -Os -Wall sinf.c -o sinf.bc
