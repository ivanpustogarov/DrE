#include ../../Makefile.defs
#
##include ../Makefile.defs
#INC = -I$(fie_root)/engine/include \
#	-I$(llvm_root)/include \
#	-I$(fie_root)/engine/lib/Core

DRE_ROOT=/home/ivan/Workspaces/DrE
LLVM_ROOT=/home/ivan/Workspaces/llvm-3.4
INC = -I$(DRE_ROOT)/include -I$(LLVM_ROOT)/include -I$(DRE_ROOT)/lib/Core

all:
	@echo "Possible targets are: linux macos"
linux:
	g++ -c -fPIC -o interrupts.o interrupts.cpp $(INC) -D__STDC_LIMIT_MACROS -D__STDC_CONSTANT_MACROS
	g++ -shared -Wl,-soname,libinterrupts.so.1 -o libinterrupts.so.1.0.1 interrupts.o -lc
	ln -sf libinterrupts.so.1.0.1 libinterrupts.so

macos:
	clang -shared -undefined dynamic_lookup $(INC) -D__STDC_LIMIT_MACROS -D__STDC_CONSTANT_MACROS  -o libinterrupts.so interrupts.cpp

clean:
	rm -f libregisters.so.1.0.1 libregisters.so registers.o \
        libinterrupts.so.1.0.1 libinterrupts.so interrupts.o \
        fake_regs.bc

#reset:
#	$(fie_root)/plugin_gen/scripts/dummy_interrupts.py $(fie_root)/plugin_gen/unique_interrupts.txt . bbl
#	make all
#
#clean:
#	rm -f *.so *.so.* *.o
