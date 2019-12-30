#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <strings.h>

//DEFINES
#define MAX 100

typedef struct _instrucao{
    char command[MAX];
    char param[MAX][MAX];
    int count;
}instrucao;
//VARS de funcionamento
//char *path = "/bin/"; //Funciona com comandos do sistema operativo

//Funcoes
int informa();
int newInstrucao();
void insertCommand(char *command);
void insertParam(char *param);
void execute();
int existsCommand();
void yyerror(char *c);
int yylex(void);