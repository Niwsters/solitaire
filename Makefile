memcheck: compile valgrind
all: build run

build:
	gcc ./src/*c -o ./bin/solitaire `sdl2-config --cflags --libs` -lSDL2_image -lm -pthread

run:
	./bin/solitaire

run-lisp:
	rlwrap ecl --load ./src/sbcl-fifo.lisp

valgrind: build
	valgrind --gen-suppressions=all --suppressions=./linux_sdl.sup --leak-check=full --show-leak-kinds=all ./bin/solitaire
