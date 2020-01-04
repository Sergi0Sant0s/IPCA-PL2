%{
    #include <stdio.h>
    #include "grammar.tab.h"
    #include "funcoes.h"

%}

VARNAME $[a-zA-Z]+
VARVALUE =[ ][^ \n\t\r]+

IGNORE [\t\r]

DAPASTA "da-pasta"[ ]
PARACADA ^"para-cada"[ ]
FIMPARA ^"fim-para""\n"

COMMANDO ^[a-z]+([ ]|\n)

TEXTO [^ \"\n$]+
ASPA "\""
SPACE [ ]
EOL "\n"
TERMINA ^termina\n

%%
{TERMINA}   { return TERMINA; }
{EOL}       { return EOL; }

{COMMANDO}  { yylval.string = strdup(yytext); yylval.string[strlen(yylval.string)-1] = '\0'; return COMMAND; }
{SPACE}     { return SPACE; }
{ASPA}      { return ASPA; }

{VARNAME}   { yylval.string = strdup(yytext+1); return VARNAME; }
{VARVALUE}  { yylval.string = strdup(yytext+2); return VARVALUE; }

{PARACADA}  { return PARACADA; }
{FIMPARA}   { return FIMPARA; }
{DAPASTA}   { return DAPASTA; }

{IGNORE}    { /*IGNORA MATCHES*/ }
{TEXTO}     { yylval.string = strdup(yytext); return TEXT; }

%%

int yywrap() { return 0;  }