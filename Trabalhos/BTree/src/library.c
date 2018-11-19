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

Each entry in the Main Data File has a struct BOOK and additional fields to organize stuff. It is represented by the struct ENTRY

Each entry in the Index File has a copy of the isbn of the book it points and the rrn of that book in the Main Data File. It is represented by a struct IDXENTRY

The whole library is represented by the struct LIBRARY, which has filepointers to the main data file and index file

ATTENTION! this library is quite spartan. It will not deal with wrong input or weird edge cases!
*/



//innitializes the library with the filepointers to the main data file and index files
//returns the lib
#define DFfilename "library.dat"
#define IDXfilename "index.dat"
//if something wrong happens, will warn you, abort and return the current state of lib
LIBRARY buildStartingLibrary(){
    LIBRARY lib;
    lib.mainFp = fopen(DFfilename, "w+");
    if(lib.mainFp == NULL){
        printf("ERROR CREATING STARTING MAIN DATA FILE\n");
        return lib;
    }
    lib.idxFp = fopen(IDXfilename, "w+");
    if(lib.idxFp == NULL){
        printf("ERROR CREATING STARTING INDEX FILE\n");
        return lib;
    }
    lib.bookCount = 0;
    
    return lib;
}

void closeLibrary(LIBRARY *lib){
    fclose(lib->mainFp);
    fclose(lib->idxFp);
    return;
}

//returns a book filled with the data sent to the function
BOOK buildBook(char title[], char isbn[], char author[], char year[]){
    BOOK newBook;
    //i'm using strncpy instead of strcpy as it guarantees the string is clear on the right side of the \0 so that the main data file doesnt look horrendous
    strncpy(newBook.title, title, sizeof(((BOOK *)NULL)->title));//this weird thing returns the size of a field in a struct
    strncpy(newBook.isbn, isbn,sizeof(((BOOK *)NULL)->isbn));
    strncpy(newBook.author, author,sizeof(((BOOK *)NULL)->author));
    strncpy(newBook.year, year,sizeof(((BOOK *)NULL)->year));
    return newBook;
}

void printBook(BOOK book){
    printf("ISBN: %s\n", book.isbn);
    printf("Title: %s\n",book.title);
    printf("\tAuthor: %s\n", book.author);
    printf("\tYear: %s\n", book.year);

    return;
}

//returns an IDXENTRY built from book
//clears rrn, does not fill it with meaningful info
IDXENTRY buildIdxEntry(BOOK book, int rrn){
    IDXENTRY entry;
    strcpy(entry.isbn, book.isbn);
    entry.rrn = rrn;

    return entry;
}

void printIdxEntry(IDXENTRY idxentry){
    printf("ISBN: %s\n", idxentry.isbn);
    printf("\t==RRN:%d\n", idxentry.rrn);

    return;
}

//currently it just appends the idxEntry. Not useful at all
//not available in library.h :)
int addIdxEntry(IDXENTRY idxEntry, LIBRARY *lib){

    fseek(lib->mainFp,0,SEEK_END);
    if (fappend(&idxEntry, sizeof(IDXENTRY),1,lib->idxFp) <= 0){//if nothing was written (0) or an error occured (-1)
        printf("ERROR ADDING INDEX ENTRY TO INDEX DATA FILE");
    }
    

    return 0;
}

//adds book to the library (in secondary mem)
//returns -1 if failed
int addBook(LIBRARY *lib, BOOK book){
    int rrn; // rrn of the new book

    fseek(lib->mainFp, 0, SEEK_END);
//can create problems!!
    rrn = (ftell(lib->mainFp)+1) / sizeof(BOOK);//pos for the n-th book

    fseek(lib->mainFp,0,SEEK_END);
    if (fappend(&book, sizeof(BOOK),1,lib->mainFp) <= 0){//if nothing was written (0) or an error occured (-1)
        printf("ERROR ADDING BOOK TO MAIN DATA FILE");
    }
    addIdxEntry(buildIdxEntry(book, rrn), lib);//adds the idxentry to indexfile
    lib->bookCount++;
    
    return 0;
}

BOOK readBookFromDF(LIBRARY *lib,int rrn){//reads the rrn-th book in the main data file        
    BOOK book;
    
    rewind(lib->mainFp);
    fseek(lib->mainFp, sizeof(BOOK)*rrn, SEEK_SET);
    if(fread(&book, sizeof(BOOK), 1, lib->mainFp) <= 0) printf("ERROR READING BOOK FROM MAIN DF\n");//read one entry
    //if(readFromFile(&book, sizeof(BOOK),rrn,lib->mainFp) <= 0) printf("ERROR READING BOOK FROM MAIN DF\n");//read one entry
    
    return book;
}

IDXENTRY readIdxEntryFromIDX(LIBRARY *lib, int rrn){//reads the n-th entry in the index file
    IDXENTRY idxEntry;
    
    rewind(lib->idxFp);
    fseek(lib->idxFp, sizeof(IDXENTRY)*rrn, SEEK_SET);
    if(fread(&idxEntry, sizeof(IDXENTRY), 1, lib->idxFp) <= 0) printf("ERROR READING INDEX ENTRY FROM INDEX FILE\n");//read one entry
    //if(readFromFile(&idxEntry, sizeof(IDXENTRY),rrn,lib->idxFp) <= 0) printf("ERROR READING BOOK FROM MAIN DF\n");//read one entry
    
    return idxEntry;
}

//searches the index file and returns the rnn of an entry in the main data file with matching isbn
//returns the rrn of the searched book in the main data file
//returns -1 if the queried key was not found
int searchBook(LIBRARY *lib, char isbn[]){
    IDXENTRY idxEntry;

//SEARCH METHOD IN HERE!!!

    //PATHETIC SEQUENCIAL SEARCH
//shit's going down here
//the loop does not stop...
    for(int counter=0 ; counter<lib->bookCount ; counter++){//while EOF not found
        idxEntry = readIdxEntryFromIDX(lib,counter);
        if(!strcmp(idxEntry.isbn, isbn)) return idxEntry.rrn;//no difference btween current index entry and queried key
    }

//SEARCH METHOD!!!

    return -1;//not found 
}

//queries the index for a book with matching key and acesses the main data file and returns that book 
BOOK queryBook(LIBRARY *lib, char isbn[]){
    BOOK book;

    int rrn; 
    rrn = searchBook(lib, isbn);
    if(rrn == -1) printf("BOOK NOT FOUND!\n");
    book = readBookFromDF(lib, rrn);//reads the rrn-th book in the main data file        

    return book;
}
