SRCFILES := $(wildcard src/*.c)

all:
	gcc $(SRCFILES) -o./bin/6502