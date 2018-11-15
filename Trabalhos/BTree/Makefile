INCLUDE = ./src/utils.c ./src/files.c ./src/library.c
INCLUDEDIR = ./include

all:
	gcc -o ./build/main ./src/main.c $(INCLUDE) -I$(INCLUDEDIR) -Wall
test:
	gcc -o ./build/test ./src/test.c $(INCLUDE) -I$(INCLUDEDIR) -Wall
runTest:
	./build/test
run:
	./build/main

clear:
	rm ./build/*
	rm ./*.dat
