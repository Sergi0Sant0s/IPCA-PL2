%{
    #include "funcoes.h"

    newInstrucao();
%}

%token COMMAND TERMINA SPACE PARAM EOL
%left COMMAND TERMINA

%type <string> COMMAND
%type <string> TERMINA
%type <string> PARAM

%union{
    char string[100];
}
%%

programa:
    instrucao    { /*existsCommand() ? printf("EXECUTA") : 0;*/}
    |   TERMINA EOL   { strcmp($1,"termina") == 0 ? exit(0) : 0; }
    ;

instrucao:
    COMMAND SPACE params EOL    { printf("\nCOMMAND: %s", COMMAND);/*insertCommand($1);*/ }
    ;

params:
    PARAM SPACE PARAM  { printf("\nPARAM: %s \nPARAM2: %s", $1,$3);/*insertParam($1);*/ }
    |   PARAM   { printf("\nPARAM: %s", PARAM);/*insertParam($1);*/ }
    ;
%%

void yyerror(char *c){
    printf("Meu erro foi: %s\n", c);
}