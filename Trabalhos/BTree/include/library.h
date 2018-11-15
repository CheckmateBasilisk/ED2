#ifndef _LIBRARY_H_
#define _LIBRARY_H_

#include<stdio.h>

typedef struct{
    char isbn[14];
    //char author[50];
    //char year[5];
}BOOK;

typedef struct{
    BOOK book;
    int rrn;//offset in the main data file
}ENTRY;


FILE *buildStartingLibrary();
BOOK buildBook(char []);
int appendDF(BOOK , FILE *);
ENTRY readEntry(int , FILE *);
void printBook(BOOK );
void printEntry(ENTRY );

#endif
