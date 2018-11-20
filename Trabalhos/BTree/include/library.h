#ifndef _LIBRARY_H_
#define _LIBRARY_H_

#include<stdio.h>
#include<math.h>

typedef struct{
    char title[50];
    char isbn[14];
    //char isbn[16];//there's something weird at runtime. Some kind of optimization making IDXENTRY occupy more bytes than it should
    char author[50];
    char year[5];
}BOOK;

typedef struct{
    char isbn[16];
    int rrn;//offset in the main data file
}IDXENTRY;

#define BTREEORDER 4
#define MAXCHILDREN BTREEORDER
#define MINXHILDREN ceil(BTREEORDER/2)
#define MAXKEYS BTREEORDER-1
#define MINKEYS 
typedef struct{
    int child[MAXCHILDREN];//array of "record pointers" to the rrn of the children in the Index File
    IDXENTRY key[MAXKEYS];//array of keys
}BTPAGE;

typedef struct{
    FILE *mainFp;//main data file
    FILE *idxFp;//index file
    int bookCount;
    /*typedef struct{
        //non-functional!!
        //header to the DF. Precedes all the Entries
    }DFHEADER;*/
}LIBRARY;

LIBRARY buildStartingLibrary();
void closeLibrary(LIBRARY *);
BOOK buildBook(char [], char [], char [], char []);
void printBook(BOOK );
IDXENTRY buildIdxEntry(BOOK , int );
void printIdxEntry(IDXENTRY );
int addBook(LIBRARY *, BOOK );
BOOK readBookFromDF(LIBRARY *,int );
IDXENTRY readIdxEntryFromIDX(LIBRARY *, int );
int searchBook(LIBRARY *, char []);
BOOK queryBook(LIBRARY *, char []);

#endif
