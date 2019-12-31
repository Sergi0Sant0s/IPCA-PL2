
typedef struct _parametro{
    char *value;
    struct _parametro *child;
}Parametro;

//Funcoes
void yyerror(char *c);
int yylex(void);



Parametro* newParametro(char *string);
Parametro* insertParametro(Parametro *lst, Parametro *param);
void Lista(Parametro *lst);

//Exit
void checkExit(char *string);