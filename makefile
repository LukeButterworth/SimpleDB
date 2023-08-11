build:
	gcc src/main.c -o bin/simpledb

build-debug:
	gcc src/main.c -o bin/simpledb -g

run:
	bin/simpledb

debug:
	gdb bin/simpledb
