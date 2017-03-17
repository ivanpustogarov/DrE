all:
	scripts/build.py .
	$(MAKE) -C interrupts all

fuzz:
	scripts/build.py . fuzz

reset:
	scripts/build.py . reset
	make all
