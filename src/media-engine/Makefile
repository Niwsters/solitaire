build-c:
	gcc test.c libtest.a `ecl-config --cflags` -o test \
	    `ecl-config --ldflags` -lecl

build-lisp:
	ecl -load compile.lisp

build: build-lisp build-c

run:
	./test

dev: build run
