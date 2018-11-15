#include<stdio.h>
#include<stdlib.h>
#include<utils.h>
#include<files.h>
#include<library.h>

#define ENTER 10

int main(int argc, char *argv[]){
    FILE *mainDF = buildStartingLibrary();
    
    appendDF(buildBook("A234567890123"), mainDF);
    //appendDF(buildBook("B234567890123"), mainDF);
    //appendDF(buildBook("C234567890123"), mainDF);
    
    /*for(int i=0;i<3;i++){
        printEntry(readEntry(i,mainDF));
    }*/    

    ENTRY entry;
    readFromFile(&entry,sizeof(ENTRY),0,mainDF);
    printEntry(entry);
    return 0;
}
