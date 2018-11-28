#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<library.h>//grants acess to structs LIBRARY, ENTRY, BOOK
#include<files.h>


#define BTREEORDER 4
#define MAXCHILDREN BTREEORDER
#define MINXHILDREN ceil(BTREEORDER/2)
#define MAXKEYS BTREEORDER-1
#define MINKEYS 
typedef struct{
    int child[MAXCHILDREN];//array of "record pointers" to the rrn of the children in the Index File
    IDXENTRY key[MAXKEYS];//array of keys
}BTPAGE;

//IMPLEMENTING A B TREE



//IMPLEMENTING A B TREE

/*
GOAL:

make a layer between the library.c and the files, implementing a b-tree
    this allows the base framework to be adapted for any method of insertion and search

INPUT 
the following functions in the library.c will call the functions here

//implementation-specific libInitialization
LIBRARY buildStartingLibrary();
    calls as buildStartingLibrary_Btree(&lib);

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

void buildStartingLibrary_Btree(LIBRARY *lib){
    lib->btreeRootRRN = -1; //descrbed in library.h
    return;
}

void addIdxEntry_Btree(LIBRARY *lib, IDXENTRY idxEntry){
    fseek(lib->mainFp,0,SEEK_END);
    if (fappend(&idxEntry, sizeof(IDXENTRY),1,lib->idxFp) <= 0){//if nothing was written (0) or an error occured (-1)
        printf("ERROR ADDING INDEX ENTRY TO INDEX DATA FILE");
    }

    return;
}

//searches the index approprately, returning the rrn of the Entry in the main data file with the corresponding isbn
//returns -1 if not found
int searchEntry_Btree(LIBRARY *lib, char isbn[]){
    IDXENTRY idxEntry;

    //sequential search
    for(int counter=0 ; counter<lib->bookCount ; counter++){//while EOF not found
        idxEntry = readIdxEntryFromIDX(lib,counter);
        if(!strcmp(idxEntry.isbn, isbn)) return idxEntry.rrn;//no difference btween current index entry and queried key
    }

    return -1;//not found 
}

void printAllBooks_Btree(LIBRARY *lib){
    BOOK book;
    for(int i=0;i<lib->bookCount;i++){
        book = readBookFromDF(lib, i);
        printBook(book);
    }

    return;
}

