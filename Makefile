memcheck: compile valgrind
all: compile run

compile:
	gcc main.c app.c util.c image.c -lSDL2 -lSDL2_image -o main

run:
	./main

valgrind:
	valgrind --gen-suppressions=all --suppressions=./linux_sdl.sup --leak-check=full --show-leak-kinds=all ./main

test:
	gcc test.c -lecl -o test
