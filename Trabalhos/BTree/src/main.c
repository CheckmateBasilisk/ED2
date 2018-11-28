#include<stdio.h>
#include<stdlib.h>
#include<utils.h>
#include<files.h>

#define ENTER 10

void printMenu(){
    printf("\ta) Inserir\n\tb) Listar Todos os Livros\n\tc) Buscar Livro\n\td) Consulta Casada\n\te) Carregar Arquivos\n\tf) Remoção (não operacional)\n\tq) sair"\n);

    return;
}


int main(int argc, char *argv[]){
    char op; //operation

    do{
        printMenu();
        scanf(" %c", &op);
        if(op == 'a'){
            //insertBook();
        }else if(op == 'b'){
            //printAllBooks();
        }else if(op == 'c'){
            //queryBook();
        }else if(op == 'd'){
            //ConsultaCasada
        }else if(op == 'e'){
            //Load Files
        }else if(op == 'f'){
            //remoção (NÂO IMPLEMENTADA)
        }else if(op == 'q'){
           //close lib 
        }else{
            printf("Comando Não Reconhecido\n");
        }

    }while(op!='q')

}
