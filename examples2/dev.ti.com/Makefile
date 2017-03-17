# Targets
FIRMWARES=msp430g2xx3_P1_01.out blink.out blink-adc.out msp430g2x33_adc10_01.out interrupt-test.out
LLVM_LL=msp430g2xx3_P1_01.ll blink.ll  msp430g2x33_adc10_01.ll interrupt-test.ll
LLVM_BITCODES=msp430g2xx3_P1_01.bc blink.bc  msp430g2x33_adc10_01.bc interrupt-test.bc

GCC_DIR =  $(HOME)/opt/ti/gcc/bin
SUPPORT_FILE_DIRECTORY = $(HOME)/opt/ti/gcc/include
CLANG_DIR =  $(HOME)/Workspaces/llvm-3.4/Release+Asserts/bin

# Please set your device # here
DEVICE = msp430g2553
DEVICE_BIG = MSP430G2553
TARGET = msp430

# Flags for msp430-elf-gcc and its linker
CC = $(GCC_DIR)/msp430-elf-gcc
GDB = $(GCC_DIR)/msp430-elf-gdb
CFLAGS = -I $(SUPPORT_FILE_DIRECTORY) -mmcu=$(DEVICE) -O2 -g
LFLAGS = -L $(SUPPORT_FILE_DIRECTORY) -T $(DEVICE).ld

# Flags for clang-3.4
CLANG = $(CLANG_DIR)/clang
#CLANG_FLAGS = -D__$(DEVICE_BIG)__ --target=$(TARGET) -I $(SUPPORT_FILE_DIRECTORY) -g -S -emit-llvm -Wall -c
CLANG_FLAGS = -D__$(DEVICE_BIG)__ --target=$(TARGET) -I../../memorymodels/symbolic/$(DEVICE) -g -emit-llvm -Wall -c

all:
	@echo "Possible targets are 'elf' and 'bitcode'"

elf: $(FIRMWARES)

bitcode: $(LLVM_BITCODES) $(LLVM_LL)

%.out : %.c
	$(CC) $(CFLAGS) $(LFLAGS) $< -o $@


# ~/Workspaces/llvm-3.4/Release+Asserts/bin/clang --target=msp430 -g -S -emit-llvm -Wall  -I../../memorymodels/symbolic/msp430g2553/  -c msp430g2xx3_P1_01.c
%.ll : %.c
	$(CLANG) $(CLANG_FLAGS) -S $< -o $@

%.bc : %.c
	$(CLANG) $(CLANG_FLAGS) $< -o $@

clean:
	rm -f $(FIRMWARES) $(LLVM_BITCODES) $(LLVM_LL)

clean-klee-out:
	rm -rf klee-out-* klee-last

#debug: all
#	$(GDB) $(DEVICE).out

#all:
#	~/Workspaces/llvm-3.4/Release+Asserts/bin/clang -g -S -emit-llvm -Wall -c main.c -o main.ll
#	~/Workspaces/llvm-3.4/Release+Asserts/bin/clang -g    -emit-llvm -Wall -c main.c -o main.bc
#
#clean:
#	rm -f main.ll main.bc
