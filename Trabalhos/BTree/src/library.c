#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<files.h>
#include<utils.h>
#include<library.h>//to recognize the types defined 

/*
The library system is divided in two files:
    * The Main Data File: that contains all entries in insertion order.
        DF will be abreviation of DataFile
    * the BTree Index File: which contains references in rrn to each entry in the library, organized in a B-Tree

Each entry in the Main Data File has a struct BOOK and additional fields to organize stuff

ATTENTION! this library is quite spartan. It will not deal with wrong input or weird edge cases!
*/

//non-functional!!
//header to the DF. Precedes all the Entries
typedef struct{

}DFHEADER;

#define DFfilename "library.dat"
FILE *buildStartingLibrary(){
    FILE *mainFp= fopen(DFfilename, "w");
    if(mainFp == NULL){
        printf("ERROR CREATING STARTING MAIN DATA FILE\n");
        return NULL;
    }
    
    return mainFp;
}

//returns a book filled with the data sent to the function
//this uses the REDUCED BOOK, with ISBN only!!!
BOOK buildBook(char isbn[]){
    BOOK newBook;
    strcpy(newBook.isbn, isbn);
    return newBook;
}

void printBook(BOOK book){
    printf("ISBN: %s\n", book.isbn);
    printf("Title:\n");
    printf("\tAuthor:\n");
    printf("\tYear:\n");

    return;
}

//returns an ENTRY built from book
//clears rrn, does not fill it with meaningful info
ENTRY buildEntry(BOOK book){
    ENTRY entry;
    entry.book = book;
    entry.rrn = -1;

    return entry;
}

void printEntry(ENTRY entry){
    printf("ISBN: %s\n", entry.book.isbn);
    printf("Title:\n");
    printf("\tAuthor:\n");
    printf("\tYear:\n");
    printf("\t==RRN:%d\n", entry.rrn);

    return;
}

//reads from MainDF the rrn-th entry and returns it
ENTRY readEntry(int rrn, FILE *mainDF){
    ENTRY entry;
    if(readFromFile(&entry, sizeof(ENTRY),rrn,mainDF) <= 0) printf("ERROR READING ENTRY FROM DF\n");
    
   return entry; //WILL RETURN SHIT if the read failed!
}

//appends the book in the ENTRY format inside fp file
//returns the nr of written blocks: 1 if succeeded, 0 if failed, -1 if error
int appendDF(BOOK book, FILE *fp){
    ENTRY newEntry = buildEntry(book);
    fseek(fp, 0, SEEK_END);
    newEntry.rrn = ftell(fp)/sizeof(ENTRY); //returns the rrn for the last ENTRY in the MainDF. This works since the rrn starts at 0 and goes to n-1
    return fappend(&newEntry, sizeof(ENTRY), 1, fp);
}

