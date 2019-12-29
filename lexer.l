%{

    #include "grammar.tab.h"

%}

COMMANDO ^[a-zA-Z0-9]+
TERMINA ^[a-zA-Z]+\n
PARAMETRO [^ \n]+
EOL \n
SPACE [ ]

%%

{COMMANDO}  {return COMMAND;}
{TERMINA}   {return TERMINA;}
{PARAMETRO} {return PARAM;}
{EOL}   {return EOL;}
{SPACE} {return SPACE;}

%%

int yywrap() { return 1; }