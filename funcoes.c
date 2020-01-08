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
        lst->type == VAR ? printf("%s",returnValue(lst->value)->value) : printf("%s", lst->value);
        //
        lst = lst->child;
    }
    printf("\n");
}

#pragma endregion

#pragma region Variables

Var* newVariable(char *name, char *value){
    if(returnValue(name) == NULL){
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
    else return editVariable(name,value);
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
Ciclo* newCiclo(char* varname, Text* folder, Instrucao *list){
    Ciclo* temp = (Ciclo*) malloc(sizeof(Ciclo));
    temp->varname = varname;
    temp->folder = folder;
    temp->list = list;
    return temp;
}

void executaCiclo(Ciclo* temp){
    struct _instrucao *aux = NULL;
    newVariable(temp->varname,"");
    char* filename;

    Text* tempFolder = temp->folder;
    char* folder = tempFolder->type == VAR ? returnValue(tempFolder->value)->value : tempFolder->value;
    if(tempFolder->child != NULL){
        tempFolder = tempFolder->child;
        while(tempFolder != NULL){ 
            strcat(folder,tempFolder->type == VAR ? returnValue(tempFolder->value)->value : tempFolder->value); 
            tempFolder = tempFolder->child; 
        }
    }

    Text* folderFiles = getContainerFolder(folder); //todos os ficheiros e pastas da pasta do ciclo

    while (folderFiles != NULL){ //Ciclo para cada ficheiro ou pasta da pasta deste ciclo
        filename = strdup(folder);
        strcat(filename,"/");
        strcat(filename,folderFiles->value);
        //
        editVariable(temp->varname, filename); //coloca o ficheiro ou pasta a correr dentro da variavel
        aux = temp->list;
        
        while (aux != NULL) //Cada instrucao dentro deste ciclo
        {
            //verifica de que tipo é a instrucao
            if(aux->type == CICLO) { executaCiclo((Ciclo *)aux->value); }
            else{ executaCommand((Command *)aux->value); } 
            //
            aux = aux->child; //proxima instucao
        }
        folderFiles = folderFiles->child; //Proximo ficheiro / pasta   
    }
}

#pragma endregion

#pragma region Comandos
Command* newCommand(char* command, Text* list){
    Command* temp = (Command*) malloc(sizeof(Command));
    temp->command = command;
    temp->list = list;
    return temp;
}

#pragma endregion

#pragma region CloseProgram
//Termina
void termina(){ 
        exit(1);
}

#pragma endregion