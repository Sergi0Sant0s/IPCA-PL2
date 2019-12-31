#include <stdio.h>
#include "grammar.tab.h"


int main() {
    printf("\n%% ");
    yyparse();
    return 0;
}


