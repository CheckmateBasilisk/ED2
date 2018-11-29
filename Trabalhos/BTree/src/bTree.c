#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<library.h>//grants acess to structs LIBRARY, ENTRY, BOOK
#include<files.h>
#include<bTree.h>


//IMPLEMENTING A B TREE

//creates a new page, empty
BTPAGE createPage(){
    BTPAGE page;
    memset(&page, '\0', sizeof(BTPAGE));
    return page;
}

#define EMPTYISBN "\0"
int findPage_step(LIBRARY *lib, int rrn, char isbn[]){
    int i;
    BTPAGE page;
    if(rrn < 0) return -1;//??
    fread(&page, sizeof(IDXENTRY), 1, lib->idxFp);
    //find which page between children:
        //hasnt reached max
        //there's still children, given rightmost are certain EMTPYISBN
        //the current key is smaller than isbn (strcmp<0)
    for(i=0; i<MAXKEYS && strcmp(page.key[i].isbn,EMPTYISBN) && strcmp(page.key[i].isbn, isbn) < 0 ; i++);
        //remember that page.key is an IDXENTRY, with char[] field

    if(i==MAXCHILDREN && page.child[i] != -1) return findPage_step(lib, page.child[i], isbn);//rightmost child, if it exists
    if(page.child[i] != -1) return findPage_step(lib, page.child[i], isbn);//left child of the first key>isbn
    return rrn;//last case & stopping point
}

//finds the page that contains the entry with the isbn
//returns the rrn of that page in the IdxFile
//returns -1 ifnot found
int findPage(LIBRARY *lib, char isbn[]){
    return findPage_step(lib, lib->btreeRootRRN, isbn);
}

//reads the rrn-th page in the idx file
//returns the read page
BTPAGE readPage(LIBRARY *lib, int rrn){
    BTPAGE page;
    fseek(lib->idxFp,rrn*sizeof(BTPAGE),SEEK_SET);
    fread(&page, sizeof(BTPAGE),1,lib->idxFp);

    return page;
}

void addIdxEntry_Btree(LIBRARY *lib, IDXENTRY idxEntry){
    if(lib->btreeRootRRN == -1){//no nodes yet. Add root!
        BTPAGE newRoot = createPage();
        newRoot.child[0] = -1;
        newRoot.key[0] = idxEntry;
        newRoot.child[1] = -1;
        lib->btreeRootRRN = (ftell(lib->idxFp)+1)/sizeof(BTPAGE);//rrn of root is 0
        fwrite(&newRoot, sizeof(BTPAGE), 1, lib->idxFp);

        printf("Successfully added Key (isbn): %s \n", newRoot.key[0].isbn);
        return;
    }

    //find appropriate page
    BTPAGE page;
    printf("W1!\n");
    page = readPage(lib,findPage(lib, idxEntry.isbn));
    printf("W2!\n");

    //see if fits
        //if fits, add neatly
        //if doesn't
            //virtual add
            //split
            //promote middle
                //recursively add above
    
    //done
    
    return;
}

void printPage(BTPAGE page){
    int i;
    printf("==========================\n");
    printf("PARENT: %d\n", page.parent);

    for(i=0;i<MAXKEYS;i++){
        printf("--------------------------\n");
        printf("CHILD[%d]: %d\n", i, page.child[i]);
        printf("--------------------------\n");
        printIdxEntry(page.key[i]);
    }
    printf("--------------------------\n");
    printf("CHILD[%d]: %d\n", i, page.child[i]);

    printf("==========================\n");
    return;

}
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

/*
void addIdxEntry_Btree(LIBRARY *lib, IDXENTRY idxEntry){
    fseek(lib->mainFp,0,SEEK_END);
    if (fappend(&idxEntry, sizeof(IDXENTRY),1,lib->idxFp) <= 0){//if nothing was written (0) or an error occured (-1)
        printf("ERROR ADDING INDEX ENTRY TO INDEX DATA FILE");
    }

    return;
}
*/

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

