CC = clang -ccc-host-triple msp430-elf -c -emit-llvm -I/home/ubuntu/embedded/analysis/model/ 

DEF = -D__MSP430__=1 -D____=1 -Wmain
INC = -I$a/model/common -I$a/model/include -include$a/model/common/isr_compat.h -include$a/model/common/msp430.h 

all:
	${CC} ${DEF} ${INC} -c abs.c -o abs.bc
	${CC} ${DEF} ${INC} -c atoi.c -o atoi.bc
	${CC} ${DEF} ${INC} -c atol.c -o atol.bc
	${CC} ${DEF} ${INC} -c bsearch.c -o bsearch.bc
	${CC} ${DEF} ${INC} -c ltoa.c -o ltoa.bc
	${CC} ${DEF} ${INC} -c sprintf.c -o sprintf.bc
	${CC} ${DEF} ${INC} -c vuprintf.c -o vuprintf.bc
