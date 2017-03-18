# Targets
LLVM_LL=main.ll
LLVM_BITCODES=main.bc

# Please set your device here
DEVICE = msp430g2553
DEVICE_BIG = MSP430G2553
TARGET = msp430

# Flags for clang-3.4
CLANG = $(LLVM_ROOT)/Release+Asserts/bin/clang
CLANG_FLAGS = -D__$(DEVICE_BIG)__ --target=$(TARGET) -I../../memorymodels/symbolic/$(DEVICE) -g -emit-llvm -Wall -c

all: bitcode

bitcode: $(LLVM_BITCODES) $(LLVM_LL)

%.ll : %.c
	$(CLANG) $(CLANG_FLAGS) -S $< -o $@

%.bc : %.c
	$(CLANG) $(CLANG_FLAGS) $< -o $@

clean:
	rm -f $(LLVM_BITCODES) $(LLVM_LL)
	rm -rf klee-out-* klee-last

