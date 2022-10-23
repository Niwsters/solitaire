memcheck: compile valgrind
dev: build-logic build-media-dev run
build: build-logic build-media

build-media:
	gcc ./src/media-engine/*c -o ./bin/solitaire \
	`sdl2-config --cflags --libs` -lSDL2_image -lm -pthread \
	./src/logic-engine/liblogic.a \
	`ecl-config --cflags --ldflags` -lecl

build-media-dev:
	gcc ./src/media-engine/*c -o ./bin/solitaire \
	`sdl2-config --cflags --libs` -lSDL2_image -lm -pthread \
	-fsanitize=address -static-libasan -g \
	./src/logic-engine/liblogic.a \
	`ecl-config --cflags --ldflags` -lecl

build-logic:
	rlwrap ecl -load ./src/logic-engine/compile.lisp

run:
	rlwrap ./bin/solitaire

valgrind: build
	valgrind --gen-suppressions=all --suppressions=./linux_sdl.sup --leak-check=full --show-leak-kinds=all ./bin/solitaire
