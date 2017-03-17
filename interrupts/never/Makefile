include ../../Makefile.defs
INC = -I$(fie_root)/engine/include -I$(llvm_root)/include -I$(fie_root)/engine/lib/Core

all:
	g++ -c -fPIC -o interrupts.o interrupts.cpp $(INC) -D__STDC_LIMIT_MACROS -D__STDC_CONSTANT_MACROS
	g++ -shared -Wl,-soname,libinterrupts.so.1 -o libinterrupts.so.1.0.1 interrupts.o -lc
	ln -sf libinterrupts.so.1.0.1 libinterrupts.so

reset:
	$a/plugin_gen/scripts/dummy_interrupts.py $a/plugin_gen/unique_interrupts.txt . never
	make all

clean:
	rm -f *.so *.so.* *.o
