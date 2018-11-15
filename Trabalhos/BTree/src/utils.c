#include<stdlib.h>
#include<stdio.h>

//returns a char* with the content read from stream until DELMITER is reached
//replaces DELIMITER with '\0'
char *readLine(FILE *stream, char DELIMITER){
    char c, *line = NULL;
    int len = 0;
    
    do{
        c = fgetc(stream);
        line = (char *) realloc(line,sizeof(char)*(len+1));
        line[len++] = c;
    }while(c!=DELIMITER);
    line[len-1] = '\0';

    return line;
}



