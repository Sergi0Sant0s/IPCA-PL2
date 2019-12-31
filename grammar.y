%{
    #include <stdio.h>
    #include <stdlib.h>
    #include "funcoes.h"

    char array[100][100];
    int count = 0;
%}

%union{
    char *string;
    struct _parametro *param;
}

%token COMMAND TERMINA PARAM EOL
%left COMMAND PARAM

%type<string> COMMAND PARAM TERMINA
%type<param> paramList

%%

s:
        COMMAND paramList EOL   { printf("\nCOMMAND: _%s_",$1); Lista($2); }
    |   TERMINA                 { checkExit($1); }
    ;

paramList:
        PARAM                   { $$ = newParametro($1); }
    |   PARAM paramList         { $$ = insertParametro($2,newParametro($1)); }

%%

void yyerror(char *c){
    printf("Meu erro foi: %s\n", c);
}