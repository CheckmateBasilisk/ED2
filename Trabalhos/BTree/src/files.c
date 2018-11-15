#include<stdio.h>
#include<stdlib.h>


//this lib deals with acessing and retrieving data from files to use in the Library system

//puts in *dest the content of the rrn-th array of elem_size bytes
//returns 1 if sucessful, 0 if no reads were performed, -1 if an error occured
//will disturb the "cursor" location inside stream
int readFromFile(void *dest, int elem_size, int rrn, FILE *stream){
    fseek(stream, rrn*elem_size, SEEK_SET);
    return fread(dest, elem_size, 1, stream);
}

//makes a fwrite appending 
//returns just like fwrite: return the number of items read or written
//will disturb the "cursor" location inside stream
int fappend(void *ptr, int size, int nmemb, FILE *stream){
    fseek(stream, 0, SEEK_END);
    return fwrite(ptr, size, nmemb, stream);
}

