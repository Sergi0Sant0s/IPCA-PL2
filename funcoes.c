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

//Termina
void checkExit(char *string){ 
    if(strcmp(string,closePrograma) == 0)
        exit(1);
}

Parametro* newParametro(char *string){
    Parametro *param = (Parametro*) malloc(sizeof(Parametro));
    param->child = NULL;
    param->value = strdup(string);
    return param;
}

Parametro* insertParametro(Parametro *lst, Parametro *param){
    param->child = lst;
    return param;
}

void Lista(Parametro *lst){
    while(lst != NULL){
        printf("\nPARAM: _%s_",lst->value);
        lst = lst->child;
    }
}
