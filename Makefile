memcheck: compile valgrind
all: build run

build:
	gcc main.c app.c util.c image.c -o ./bin/solitaire `sdl2-config --cflags --libs` -lSDL2_image

run:
	./bin/solitaire

valgrind:
	valgrind --gen-suppressions=all --suppressions=./linux_sdl.sup --leak-check=full --show-leak-kinds=all ./main

test:
	gcc test.c -lecl -o test
