# Targets
LLVM_LL=main.ll
LLVM_BITCODES=main.bc

SUPPORT_FILE_DIRECTORY = $(HOME)/opt/ti/gcc/include
CLANG_DIR =  $(HOME)/Workspaces/llvm-3.4/Release+Asserts/bin

# Please set your device # here
DEVICE = msp430g2553
DEVICE_BIG = MSP430G2553
TARGET = msp430

LFLAGS = -L $(SUPPORT_FILE_DIRECTORY) -T $(DEVICE).ld

# Flags for clang-3.4
CLANG = $(CLANG_DIR)/clang
CLANG_FLAGS = -D__$(DEVICE_BIG)__ --target=$(TARGET) -I../../memorymodels/symbolic/$(DEVICE) -g -emit-llvm -Wall -c

all: bitcode
	

elf: $(FIRMWARES)

bitcode: $(LLVM_BITCODES) $(LLVM_LL)

%.ll : %.c
	$(CLANG) $(CLANG_FLAGS) -S $< -o $@

%.bc : %.c
	$(CLANG) $(CLANG_FLAGS) $< -o $@

clean:
	rm -f $(LLVM_BITCODES) $(LLVM_LL)

clean-klee-out:
	rm -rf klee-out-* klee-last

