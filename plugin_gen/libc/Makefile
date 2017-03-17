CC=msp430-gcc


include ../Makefile

all: $(LIBC_OBJS)

%.bc: %.c
	$(CC) $(CFLAGS) -c $< -o$@
