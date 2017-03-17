all:
	clang -ccc-host-triple msp430-elf -I. -I../include -D__MSP430__=1 symbex_intrinsics.c -emit-llvm -c -o symbex_intrinsics.bc
