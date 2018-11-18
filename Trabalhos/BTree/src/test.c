#include<stdio.h>
#include<stdlib.h>
#include<utils.h>
#include<files.h>
#include<library.h>

#define ENTER 10


int main(int argc, char *argv[]){
    LIBRARY lib = buildStartingLibrary();


    BOOK book = buildBook("The Great Gatsby","A234567890123","Scott Fitzgerald", "1922");
    addBook(&lib, book);
    book = buildBook("Venus In Furs","B234567890123","Leopold von Sacher-Masoch", "1870");
    addBook(&lib, book);
    book = buildBook("Interview with the Vampire","C234567890123","Anne Rice", "1968");
    addBook(&lib, book);

    closeLibrary(&lib);

}
