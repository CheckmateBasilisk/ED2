#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<files.h>
#include<utils.h>
#include<library.h>//to recognize the types defined 
#include<bTree.h>

/*
The library system is divided in three files:
    * The Main Data File: that contains all entries in insertion order.
        DF will be abreviation of DataFile
    * the BTree Index File: which contains references in rrn to each entry in the library, organized in a B-Tree
    * the LibConfig File: which contains the last state the lib struct had in a previous run. Will contain critical info, such as entryCount and specific implementation data, such as the root of a Btree used to order the indexEnties

Each entry in the Main Data File has a struct BOOK and additional fields to organize stuff. It is represented by the struct ENTRY

Each entry in the Index File has a copy of the isbn of the book it points and the rrn of that book in the Main Data File. It is represented by a struct IDXENTRY

The only content in the LibConfig File is the previous state of the lib struct. Nothing more. Saving the current state is as easy as dumping it into it, as when the lib is initialized (through new files or reading old ones) the libConfig is wiped.

The whole library is represented by the struct LIBRARY, which has filepointers to the main data file and index file, as well as a count of the number of entries (bookCount) and the following implementation-specific fields:
    - int BtreeRoot: the rrn of the BtreePage of the root-page

ATTENTION! this library is quite spartan. It will not deal with wrong input or weird edge cases!
*/



//innitializes the library with the filepointers to the main data file and index files
//also creates a libConfig file, that keeps the data from a previous library
//returns the lib
#define DFfilename "library.dat"
#define IDXfilename "index.dat"
#define LIBCONFIGfilename "libConfig.dat"
//if something wrong happens, will warn you, abort and return the current state of lib
LIBRARY buildStartingLibrary(){
    LIBRARY lib;
    printf("starting new Library\n");
    lib.mainFp = fopen(DFfilename, "w+");
    if(lib.mainFp == NULL){
        printf("ERROR CREATING STARTING MAIN DATA FILE\n");
        return lib;
    }
    printf("\tcreating main data file...\n");
    lib.idxFp = fopen(IDXfilename, "w+");
    if(lib.idxFp == NULL){
        printf("ERROR CREATING STARTING INDEX FILE\n");
        return lib;
    }
    printf("\tcreating index file...\n");
    lib.libConfigFp= fopen(LIBCONFIGfilename, "w+");
    if(lib.idxFp == NULL){
        printf("ERROR CREATING LIBCONFIG FILE\n");
        return lib;
    }
    printf("\tcreating libconfig file...\n");
    lib.bookCount = 0;

    //IMPLEMENTATION-SPECIFIC INITIALIZATION
    buildStartingLibrary_Btree(&lib);
    //IMPLEMENTATION-SPECIFIC INITIALIZATION
    
    return lib;
}

//tries to open main data file and indexFile
//if either fails, 
LIBRARY openLibrary(){
    LIBRARY lib;

    FILE *aux = fopen(LIBCONFIGfilename,"r+");
    if(aux == NULL){
        printf("ERROR OPENING STARTING LIBCONFIG FILE\n");
        printf("\tINITIALIZING NEW LIBRARY FILES\n");
        return buildStartingLibrary();
    }
    printf("restoring previous libstate...\n");
    fread(&lib, sizeof(LIBRARY), 1, aux);
    fclose(aux);
    lib.libConfigFp = fopen(LIBCONFIGfilename ,"w+");
    //guarantees the pointer points to the right file after being overwritten by the content of that same file. confusing...
    //also creates a new libConfigFile to store the state of the current lib when the used is finished with it

    lib.mainFp = fopen(DFfilename, "r+");
    if(lib.mainFp == NULL){
        printf("ERROR OPENING STARTING MAIN DATA FILE\n");
        printf("\tINITIALIZING NEW LIBRARY FILES\n");
        fclose(lib.libConfigFp);//closes the libConfigFP, preparing lib to start anew
        return buildStartingLibrary();
    }
    printf("\tmainFile opened sucessfully\n");
    lib.idxFp = fopen(IDXfilename, "r+");
    if(lib.idxFp == NULL){
        printf("ERROR OPENING STARTING INDEX FILE\n");
        printf("\tINITIALIZING NEW LIBRARY FILES\n");
        fclose(lib.libConfigFp);//closes the libConfigFP, preparing lib to start anew
        fclose(lib.mainFp);//closes the mainFp, preparing lib to start anew
        return buildStartingLibrary();
    }
    printf("\tindexFile opened sucessfully\n");
    
    //IMPLEMENTATION-SPECIFIC INITIALIZATION
    //none needed for Btree, as the root is alredy in the LibConfig file
    //IMPLEMENTATION-SPECIFIC INITIALIZATION

    return lib;
}

void closeLibrary(LIBRARY *lib){
    fclose(lib->mainFp);
    fclose(lib->idxFp);
    //dumps into libconfig the laststate of lib
    lib->mainFp = NULL;
    lib->idxFp = NULL;
    fseek(lib->libConfigFp, 0, SEEK_SET);
    fwrite(lib, sizeof(LIBRARY), 1, lib->libConfigFp);//dumps into libconfigFile the current state of lib, which should be empty
    
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

//adds idxEntry into the index file approprately, calling the functions in the extra library
int addIdxEntry(IDXENTRY idxEntry, LIBRARY *lib){

//INDEXING METHOD!!!
    addIdxEntry_Btree(lib, idxEntry);//adds idxEntry to the indexFile
//INDEXING METHOD!!!

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

//reads the n-th entry in the index file. Will not care about the internal organization of the idxFile. SHould be avoided at all costs!!!!
IDXENTRY readIdxEntryFromIDX(LIBRARY *lib, int rrn){
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

//SEARCH METHOD IN HERE!!!
    return searchEntry_Btree(lib, isbn);
//SEARCH METHOD!!!

}

//queries the index for a book with matching key and acesses the main data file and returns that book 
BOOK queryBook(LIBRARY *lib, char isbn[]){
    int rrn; 
    BOOK book;

    rrn = searchBook(lib, isbn);
    if(rrn == -1) printf("BOOK NOT FOUND!\n");
    book = readBookFromDF(lib, rrn);//reads the rrn-th book in the main data file        

    return book;
}

//prints all books in order
void printAllBooks(LIBRARY *lib){

    //ACESS METHOD!
    printAllBooks_Btree(lib);
    //ACESS METHOD!

    return;
}
