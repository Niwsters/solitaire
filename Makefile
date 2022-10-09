memcheck: compile valgrind
all: build run-media

build:
	gcc ./src/media-engine/*c -o ./bin/solitaire `sdl2-config --cflags --libs` -lSDL2_image -lm -pthread

run-media:
	./bin/solitaire

run-logic:
	rlwrap ecl --load ./src/logic-engine/logic.lisp

valgrind: build
	valgrind --gen-suppressions=all --suppressions=./linux_sdl.sup --leak-check=full --show-leak-kinds=all ./bin/solitaire
