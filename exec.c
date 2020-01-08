//INCLUDES
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <strings.h>
#include <unistd.h>
//
#include "grammar.tab.h"
#include "funcoes.h"

//Path default execs
char *path = "./exec/";
//char *path = "/bin/"; //Funciona com comandos do sistema operativo

//Verifica se existe o comando
//1 = encontrado
//0 = não encontrado
int existsCommand(char *command){
    struct dirent *de;
    struct stat buf;
    DIR *dr = opendir(path);

    if (dr == NULL)  return 0; //Pasta não existe

    //Corre cada pasta/ficheiro encontrado
    while ((de = readdir(dr)) != NULL) {
        stat(de->d_name, &buf);
        if(strcmp(de->d_name,command) == 0) //Compara para ver se existe o comando
            return 1;
    }
    return 0;
}

//Vai buscar todos os ficheiros e pastas de uma pasta
Text* getContainerFolder(char* folder){
    Text* list = NULL, *last;
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir (folder)) != NULL) {
        /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != NULL) {
            if(list == NULL){
                list = (Text*) malloc(sizeof(Text));
                list->value = ent->d_name;
                list->child = NULL;  
                last = list; 
            }
            else{
                last->child = (Text*) malloc(sizeof(Text));
                last = last->child;
                last->value = ent->d_name;
                last->child = NULL;    
            }
        }
        closedir (dir);
    }
    return list;
}

//Executa command
int executaCommand(Command *aux){
    Text* temp = aux->list;
    char* filename = strdup(path); 
    strcat(filename,aux->command);    //Coloca o comando com o formato "path/command"
    //
    if(strcmp(aux->command,"acrescenta") == 0)  commandAcrescenta(aux);
    else if(strcmp(aux->command,"print") == 0)  printTexts(temp);
    else if(existsCommand(aux->command)){
        while(temp != NULL){
            if(strcmp(temp->value," ") != 0){ //Verifica se se trata de espacos
                char* array[3];
                //
                array[0] = aux->command;
                array[1] = temp->type == VAR ? returnValue(temp->value)->value : temp->value;
                array[2] = NULL;
                execute(filename,array);
            }
            temp = temp->child;
        }
    }
    else {printf("O comando %s não existe.\n", aux->command); return 0; }
    return 1;
}

int commandAcrescenta(Command* aux){
    Text* temp = aux->list;
    //
    char* filename = strdup(path); 
    strcat(filename,aux->command);    //Coloca o comando com o formato "path/command"
    char* firstParam; 

    while(temp != NULL) { //memoriza primeiro parametro que não é espaço
        if(!isspace((unsigned char)*temp->value)){
            firstParam = temp->type == VAR ? returnValue(temp->value)->value : temp->value;
            temp = temp->child; //inicia com o segundo parametro
            break;
        }
        temp = temp->child;
    }
    //
    if(temp == NULL) { printf("É necessario pelo menos 2 parametros.\n"); return 0; }
    //
    while(temp != NULL){
        if(!isspace((unsigned char)*temp->value)){ //Verifica se se trata de espaco
            char* array[4];
            //
            array[0] = aux->command;
            array[1] = firstParam;
            array[2] = temp->type == VAR ? returnValue(temp->value)->value : temp->value;
            array[3] = NULL;
            execute(filename,array);
        }
        temp = temp->child;
    }
    return 1;
}

//faz a execução de um Text
void execute(char *command, char **array){
    //criação de um processo filho
    int pid = fork();
    if(pid == 0)
        execvp(command, array);
    else
        wait(NULL); //espera que o processo filho termine
}

#pragma endregion