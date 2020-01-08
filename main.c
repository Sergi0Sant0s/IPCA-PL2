#include <stdio.h>
#include "grammar.tab.h"
#include "funcoes.h"


int main() {
    do{
        printf("================================================================================================\n");
        yyparse();
    }while(1);
    //
    return 0;
}


