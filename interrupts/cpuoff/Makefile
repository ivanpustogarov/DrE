PLATFORM= $(shell uname)
DRE_ROOT=../../
INCLUDE_DRE = -I$(DRE_ROOT)/include -I$(DRE_ROOT)/lib/Core

all:
ifeq ($(LLVM_ROOT),)
	$(error Set variable LLVM_ROOT to the llvm-3.4 path.)
endif
	$(eval INCLUDE_LLVM=-I$(LLVM_ROOT)/include)
ifeq ($(PLATFORM),Linux)
	g++ -c -fPIC -o interrupts.o interrupts.cpp $(INCLUDE_DRE) $(INCLUDE_LLVM) -D__STDC_LIMIT_MACROS -D__STDC_CONSTANT_MACROS
	g++ -shared -Wl,-soname,libinterrupts.so.1 -o libinterrupts.so.1.0.1 interrupts.o -lc
	ln -sf libinterrupts.so.1.0.1 libinterrupts.so
else
ifeq ($(PLATFORM),Darwin)
	clang -shared -undefined dynamic_lookup $(INCLUDE_DRE) $(INCLUDE_LLVM) -D__STDC_LIMIT_MACROS -D__STDC_CONSTANT_MACROS  -o libinterrupts.so interrupts.cpp
endif
endif

clean:
	rm -f libregisters.so.1.0.1 libregisters.so registers.o \
        libinterrupts.so.1.0.1 libinterrupts.so interrupts.o \
        fake_regs.bc

