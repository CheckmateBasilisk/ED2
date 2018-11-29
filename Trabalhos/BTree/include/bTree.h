#ifndef _BTREE_H_
#define _BTREE_H_

#include<library.h>

//this bullshit works:
//  sizeof(((BOOK *)NULL)->isbn); //size of the field isbn

#define BTREEORDER 4
#define MAXCHILDREN BTREEORDER
#define MINXHILDREN ceil(BTREEORDER/2)
#define MAXKEYS BTREEORDER-1
#define MINKEYS 
typedef struct{
    int parent;//rrn of the parent page
    int child[MAXCHILDREN];//array of "record pointers" to the rrn of the children in the Index File
    IDXENTRY key[MAXKEYS];//array of keys
    //int keyCount;
}BTPAGE;

void printPage(BTPAGE );
void addIdxEntry_Btree(LIBRARY *, IDXENTRY );
int searchEntry_Btree(LIBRARY *, char []);
void printAllBooks_Btree(LIBRARY *);
void buildStartingLibrary_Btree(LIBRARY *);
BTPAGE readPage(LIBRARY *, int );

#endif
