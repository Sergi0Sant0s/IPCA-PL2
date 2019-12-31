//INCLUDES
#include "grammar.tab.h"
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <strings.h>
#include "funcoes.h"

//VARS de funcionamento
//char *path = "/bin/"; //Funciona com comandos do sistema operativo
char *closePrograma = "termina";
char *path = "./exec/";

#pragma region Parametros

//Cria novo parametro
Parametro* newParametro(char *string){
    Parametro *param = (Parametro*) malloc(sizeof(Parametro));
    param->child = NULL;
    param->value = strdup(string);
    return param;
}

//Insere novo parametro na lista
Parametro* insertParametro(Parametro *lst, Parametro *param){
    param->child = lst;
    return param;
}

//Devolve o numero de parametros existentes
int countParameters(Parametro *lst){
    Parametro *aux = lst;
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

//executar cada parametro encontrado
int instrucao(char *command, Parametro *lst){
    char *aux = strdup(path);  
    strcat(aux,command);    //Coloca o comando com o formato "path/command"

    if(strcmp(command,"acrescenta") == 0){
        //Por fazer
        return 1;
    }
    else{
        while(lst != NULL){
            execute(aux,lst->value);
            lst = lst->child;
        }
        return 1;
    }
}

//faz a execução de um parametro
int execute(char *command, char *parametro){
    
    char *array[2];
    //
    array[0] = command;
    array[1] = parametro;
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
    Var *newVariable(Var *last, char *name, char*value){
        Var *variable = (Var*) malloc(sizeof(Var));
        variable->next = NULL;
        variable->name = strdup(name);
        variable->value = strdup(value);
        last->next = variable;
        return last;
    }

    Var *returnVariable(Var *lst, char *name){
        Var *aux = lst;
        while (aux != NULL)
        {
            if(strcmp(aux->name,name) == 0)
                return aux;
            aux = aux->next;
        }
        return NULL;
    }
#pragma endregion

#pragma region CloseProgram
//Termina
void checkExit(char *string){ 
    if(strcmp(string,closePrograma) == 0)
        exit(1);
}

#pragma endregion