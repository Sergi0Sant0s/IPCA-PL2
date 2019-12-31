%{
    #include <stdio.h>
    #include <stdlib.h>
    #include "funcoes.h"

    Var *lst = (Var*) malloc(sizeof(Var));
    lst->next = NULL;
    last = &lst;
%}

%union{
    char *string;
    struct _parametro *param;
}

%token COMMAND TERMINA PARAM VARNAME VARVALUE EOL
%left COMMAND PARAM VARNAME VARVALUE

%type<string> COMMAND PARAM VARNAME VARVALUE TERMINA
%type<param> paramList

%%

s:
        COMMAND paramList EOL   {   if(existsCommand($1)) 
                                        if(instrucao($1,$2)) printf("Terminou o comando %s\n", $1);
                                        else printf("Nao foi possivel executar o comando %s\n.", $1);
                                    else    printf("O comando %s não existe\n",$1); 
                                    return 0;
                            }
    |   VARNAME VARVALUE EOL    {   newVariable(last,$1,$2); }
    |   TERMINA                 {   checkExit($1); return 0;}
    ;

paramList:
        PARAM paramList         {   $$ = insertParametro($2,newParametro($1)); }
    |   PARAM                   {   $$ = newParametro($1); }
    |   VARNAME                 { 
                                    Var *aux = returnVariable(lst,$1);
                                    lst != NULL ? $$ = newParametro(aux->value)
                                    : (printf("A variavel %s nao existe.\n",$1), return 0); 
                                }
%%

void yyerror(char *c){
    printf("\nErro: %s\n", c);
}