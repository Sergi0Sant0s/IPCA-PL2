//INCLUDES
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <strings.h>
#include <unistd.h>
//
#include "grammar.tab.h"
#include "funcoes.h"

//VARS de funcionamento
//char *path = "/bin/"; //Funciona com comandos do sistema operativo
char *closePrograma = "termina";
char *path = "./exec/";

Var *vList = NULL, *vLast;

#pragma region Texts

//Cria novo Text
Text* newText(char *string, int type){
    Text *temp = (Text*) malloc(sizeof(Text));
    temp->child = NULL;
    temp->value = strdup(string);
    temp->type = type;
    return temp;
}

//Insere novo Text na lista
Text* insertText(Text *lst, Text *temp){
    temp->child = lst;
    return temp;
}

//Print Texts
void printTexts(Text *lst){
    while(lst != NULL){
        printf("%s ",lst->value);
        lst = lst->child;
    }
    printf("\n");
}

//Devolve o numero de Texts existentes
int countText(Text *lst){
    Text *aux = lst;
    int count = 0;
    while(aux != NULL){
        count++;
        aux = aux->child;
    }
    //
    return count;
}

#pragma endregion

#pragma region Execute
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

//executar cada Text encontrado
int executaInstrucao(Instrucao *inst){
    /*if(inst->type == CICLO){

    }
    else{
        
    }*/
    return 1;
}

int executaCommand(Command *aux){
    char *filename = strdup(path);  
    strcat(filename,aux->command);    //Coloca o comando com o formato "path/command"

    if(strcmp(aux->command,"acrescenta") == 0){
        //Por fazer
        return 1;
    }
    else if(strcmp(aux->command,"print") == 0){
        printTexts(aux->list);
        return 1;
    }
    else{
        while(aux->list != NULL){
            if(strcmp(aux->list->value, " ") != 0)
                execute(filename,aux->list->value);
            aux->list = aux->list->child;
        }
        return 1;
    }
    return 0;
}

int executeCiclo(Ciclo *aux){
    return 1;
}

//faz a execução de um Text
void execute(char *command, char *Text){
    
    char* array[2];
    //
    array[0] = command;
    array[1] = Text;
    array[2] = NULL;

    //criação de um processo filho
    int pid = fork();
    if(pid == 0)
        execvp(command, array);
    else
        wait(NULL); //espera que o processo filho termine
}

#pragma endregion

#pragma region Variables

Var* newVariable(char *name, char *value){
    if(vList == NULL){
        vList = (Var*) malloc(sizeof(Var));
        vList->name = strdup(name);
        vList->value = strdup(value);
        vList->next = NULL;
        vLast = vList;
    }
    else{
        vLast->next = (Var*) malloc(sizeof(Var));
        vLast = vLast->next;
        vLast->name = strdup(name);
        vLast->value = strdup(value);
        vLast->next = NULL;
    }    
    return vLast;
}

Var* editVariable(char *name, char *value){
        Var *aux = vList;
        while (aux != NULL)
        {
            if(strcmp(aux->name,name) == 0) { aux->value = strdup(value); return aux;}
            aux = aux->next;
        }
        //
        return NULL;
}

Var* returnValue(char *varname) {
    Var *aux = vList;
    while (aux != NULL)
    {
        if(strcmp(aux->name,varname) == 0)  return aux;
        aux = aux->next;
    }
    return NULL;
}

#pragma endregion

#pragma region Instrucoes
Instrucao* newInstrucao(void *value, int type){
        Instrucao* aux = (Instrucao*) malloc(sizeof(Instrucao));
        aux->value = value;
        aux->type = type;
        aux->child = NULL;
        return aux;
}

Instrucao* insertInstrucao(Instrucao *lst, Instrucao *last){
        last->child = lst;
        return last;
}

#pragma endregion

#pragma region Ciclos
Ciclo* newCiclo(char* varname, char* folder, Instrucao *list){
    Ciclo* temp = (Ciclo*) malloc(sizeof(Ciclo));
    temp->varname = varname;
    temp->folder = folder;
    temp->list = list;
    return temp;
}

#pragma endregion

#pragma region Comandos
Command* newCommand(char* command, Text* list){
    Command* temp = (Command*) malloc(sizeof(Command));
    temp->command = command;
    temp->list = list;
    return temp;
}

void teste(Ciclo* temp){
    printf("\nCICLO INSERIDO: varname: %s | folder: %s\n", temp->varname, temp->folder);
    while (temp->list != NULL)
    {
        if(temp->list->type == CICLO){
            teste(temp->list->value);
        }
        else{
            printf("\n\tCICLO: %s | COMMAND: %s", temp->varname, ((Command*)temp->list->value)->command);
        }
        temp->list = temp->list->child;
        
    }
    
}

#pragma endregion

#pragma region CloseProgram
//Termina
void termina(){ 
        exit(1);
}

#pragma endregion