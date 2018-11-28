INCLUDE = ./src/utils.c ./src/files.c ./src/library.c ./src/bTree.c
INCLUDEDIR = ./include

all:
	gcc -o ./build/main ./src/main.c $(INCLUDE) -I$(INCLUDEDIR) -Wall -lm
test:
	gcc -o ./build/test ./src/test.c $(INCLUDE) -I$(INCLUDEDIR) -Wall -lm
runtest:
	./build/test
run:
	./build/main

clear:
	rm ./build/*
	rm ./*.dat
