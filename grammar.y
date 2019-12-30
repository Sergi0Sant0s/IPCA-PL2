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
        instrucao EOL   { /*existsCommand() ? printf("EXECUTA") : 0;*/}
    |   close EOL { exit(0) : 0; }
    ;
close:
        TERMINA { $$ = strcmp($1,"termina") == 0 ? 1 : 0; }

instrucao:
        COMMAND SPACE params    { printf("\nCOMMAND: %s", COMMAND);/*insertCommand($1);*/ }
    ;

params:
        SPACE PARAM  { printf("\nPARAM: %s", $1);/*insertParam($1);*/ }
    |   PARAM   { printf("\nPARAM: %s", PARAM);/*insertParam($1);*/ }
    ;
%%

void yyerror(char *c){
    printf("Meu erro foi: %s\n", c);
}