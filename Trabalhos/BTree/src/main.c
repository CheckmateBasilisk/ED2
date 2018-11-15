#include<stdio.h>
#include<stdlib.h>
#include<utils.h>
#include<files.h>

#define ENTER 10

int main(int argc, char *argv[]){
    char *line = readLine(stdin, ENTER);

    printf("%s\n", line);
    free(line);
    return 0;
}
