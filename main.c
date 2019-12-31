#include <stdio.h>
#include "grammar.tab.h"


int main() {
    do{
        printf("%% ");
        yyparse();
    }while(1);
    
    return 0;
}


