#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<library.h>//grants acess to structs LIBRARY, ENTRY, BOOK


#define BTREEORDER 4
#define MAXCHILDREN BTREEORDER
#define MINXHILDREN ceil(BTREEORDER/2)
#define MAXKEYS BTREEORDER-1
#define MINKEYS 
typedef struct{
    int child[MAXCHILDREN];//array of "record pointers" to the rrn of the children in the Index File
    IDXENTRY key[MAXKEYS];//array of keys
}BTPAGE;

/*
GOAL:

make a layer between the library.c and the files, implementing a b-tree
    this allows the base framework to be adapted for any method of insertion and search

INPUT 
the following functions in the library.c will call the functions here

//not available in the library.h
int addIdxEntry(IDXENTRY idxEntry, LIBRARY *lib);
    calls as addIdxEntry_Btree(LIBRARY *lib, ENTRY idxEntry);

//available in the library.h
//returns the rrn of the book searched 
int searchBook(LIBRARY *lib, char isbn[]);
    calls as searchEntry_Btree(LIBRARY *lib, ENTRY entry);

//available in the library.h
//prints the B-Tree in-order
void printAllBooks(LIBRARY *lib);
    calls as printAllBooks_Btree(LIBRARY *lib);


*/

