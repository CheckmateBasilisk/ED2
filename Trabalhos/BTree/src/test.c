#include<stdio.h>
#include<stdlib.h>
#include<utils.h>
#include<files.h>
#include<library.h>

#define ENTER 10


int main(int argc, char *argv[]){
    LIBRARY lib = buildStartingLibrary();


    printf("Adding books to  Library\n");
    BOOK book = buildBook("The Great Gatsby","A234567890123","Scott Fitzgerald", "1922");
    addBook(&lib, book);
    book = buildBook("Venus In Furs","B234567890123","Leopold von Sacher-Masoch", "1870");
    addBook(&lib, book);
    book = buildBook("Interview with the Vampire","C234567890123","Anne Rice", "1968");
    addBook(&lib, book);

    int op;
    do{
        printf("operation:\n\t0. quit\n\t1. queryBook\n\t2. printAllBooks\n");
        scanf(" %d", &op);
        if(op==1){
            char isbn[14];
            scanf(" %s", isbn);
            printBook(queryBook(&lib,isbn));
        }else if(op==2){
            printAllBooks(&lib);
        }
    }while(op!= 0);
    printf("Exiting\n");
    /*
    IDXENTRY idxEntry;
    for(int i=0;i<lib.bookCount;i++){
        book = readBookFromDF(&lib, i);
        idxEntry = readIdxEntryFromIDX(&lib, i);
        printBook(book);
        printIdxEntry(idxEntry);
    }
    */

    //printAllBooks(&lib);

    /*
    book = queryBook(&lib,"B234567890123");
    printBook(book);
    */

    closeLibrary(&lib);

    return 0;

}
