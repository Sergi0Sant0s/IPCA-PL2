%{

    #include "grammar.tab.h"
    #include "funcoes.h"

%}

/*
{VARNAME}    { yylval.str = strdup(yytext+1); return VAR_NAME; }
{VARVALUE}     { yylval.str = strdup(yytext+1); return VAR_VALUE; }

VARNAME $"[a-z]+
VARVALUE :[a-z]+
*/

COMMANDO ^[a-zA-Z0-9]+
TERMINA ^[a-zA-Z]+\n
PARAMETRO [^ \n]+
EOL \n
SPACES [ ]+



%%

{COMMANDO}  {yylval.string = strdup(yytext); return COMMAND;}
{PARAMETRO} {yylval.string = strdup(yytext); return PARAM;}

{SPACES} { /* IGNORA ESPACOS */ }

{EOL}   {return EOL;}
{TERMINA}   { yylval.string = strdup(yytext); yylval.string[strlen(yylval.string) - 1] = '\0'; return TERMINA; }

%%

int yywrap() { return 0; }