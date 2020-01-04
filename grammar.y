%{
    #include <stdio.h>
    #include <stdlib.h>
    #include "funcoes.h"
%}

%union{
    char *string;
    struct _text *text;
    struct _ciclo *ciclo;
    struct _command *command;
    struct _instrucao *instrucao;
    struct _var *variavel;
}

%token COMMAND TEXT SPACE VARNAME VARVALUE ASPA PARACADA DAPASTA FIMPARA EOL TERMINA


%type<string> COMMAND TEXT SPACE VARNAME VARVALUE
%type<text> textList
%type<ciclo> ciclo
%type<instrucao> instrucao
%type<command> command
%type<variavel> variavel

%%

s:
        variavel                    {   if($1 != NULL) printf("Variavel: %s | Valor: %s\n",$1->name,$1->value); return 0;}
    |   ciclo                       {   teste($1); return 0; }   
    |   command                     {   printf("result command: %s\n",$1->command); /*execute($1);*/ return 0;}
    ;

variavel:
        VARNAME SPACE VARVALUE EOL  {  $$ = returnValue($1) == NULL ? newVariable($1,$3) : editVariable($1,$3); }
    |   VARNAME EOL                 {  $$ = returnValue($1); }
    ;

command:
        COMMAND ASPA textList ASPA EOL  { $$ = newCommand($1,$3); }
    |   COMMAND textList EOL            { $$ = newCommand($1,$2); }
    |   TERMINA                         { termina(); }
    ;

textList:
        TEXT textList               { $$ = insertText($2,newText($1, TXT)); }
    |   VARNAME textList            { $$ = insertText($2,newText($1, VAR)); }
    |   TEXT                        { $$ = newText($1, TXT); }
    |   SPACE                       { $$ = newText($1, TXT); }
    |   VARNAME                     { $$ = newText($1, VAR); }
    ;

instrucao:
        command instrucao           { $$ = insertInstrucao($2,newInstrucao($1,CMD)); }
    |   ciclo instrucao             { $$ = insertInstrucao($2,newInstrucao($1,CICLO)); }
    |   command                     { $$ = newInstrucao($1,CMD); }
    |   ciclo                       { $$ = newInstrucao($1,CICLO);}
    ;

ciclo:
        PARACADA VARNAME SPACE DAPASTA TEXT EOL instrucao FIMPARA  { $$ = newCiclo($2,$5,$7); }
    ;

%%

void yyerror(char *c){ printf("\nErro: %s",c);/* ... */}