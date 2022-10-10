memcheck: compile valgrind
dev: build-dev run-media

build:
	gcc ./src/media-engine/*c -o ./bin/solitaire `sdl2-config --cflags --libs` -lSDL2_image -lm -pthread

build-dev:
	gcc ./src/media-engine/*c -o ./bin/solitaire `sdl2-config --cflags --libs` -lSDL2_image -lm -pthread -fsanitize=address -static-libasan -g

build-logic:
	rlwrap ecl --load ./src/logic-engine/compile.lisp

run-media:
	./bin/solitaire

run-logic:
	rlwrap ecl --load ./src/logic-engine/logic.lisp

run: run-media & run-logic

valgrind: build
	valgrind --gen-suppressions=all --suppressions=./linux_sdl.sup --leak-check=full --show-leak-kinds=all ./bin/solitaire
