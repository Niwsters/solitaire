memcheck: compile valgrind
all: build run

build:
	gcc ./src/*c -o ./bin/solitaire `sdl2-config --cflags --libs` -lSDL2_image -lm

run:
	./bin/solitaire

valgrind:
	valgrind --gen-suppressions=all --suppressions=./linux_sdl.sup --leak-check=full --show-leak-kinds=all ./bin/solitaire
