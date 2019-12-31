%{

    #include "grammar.tab.h"
    #include "funcoes.h"

%}

/*



*/

COMMANDO ^[a-zA-Z0-9]+
TERMINA ^[a-zA-Z]+\n
PARAMETRO [^ \n]+

VARNAME $[a-zA-Z0-9]+
VARVALUE =[ ]*[^ \n]+

EOL \n
SPACES [ ]+



%%

{VARNAME}    { yylval.string = strdup(yytext+1); return VARNAME; }
{VARVALUE}     { yylval.string = strdup(yytext+2); return VARVALUE; }

{COMMANDO}  {yylval.string = strdup(yytext); return COMMAND;}
{PARAMETRO} {yylval.string = strdup(yytext); return PARAM;}

{SPACES} { /* IGNORA ESPACOS */ }


{EOL}   {return EOL;}
{TERMINA}   { yylval.string = strdup(yytext); yylval.string[strlen(yylval.string) - 1] = '\0'; return TERMINA; }

%%

int yywrap() { return 0; }