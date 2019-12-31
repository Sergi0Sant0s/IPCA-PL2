
typedef struct _parametro{
    char *value;
    struct _parametro *child;
}Parametro;

typedef struct _var{
    char *name;
    char *value;
    struct _parametro *next;
}Var;

//Funcoes
void yyerror(char *c);
int yylex(void);


//EXEC
int existsCommand(char *command);
int execute(char *command, char *parametro);
int instrucao(char *command, Parametro *lst);

//Armazenamento de parametros
Parametro* newParametro(char *string);
Parametro* insertParametro(Parametro *lst, Parametro *param);

//Variables
Var *newVariable(Var *last, char *name, char*value);
Var *returnVariable(Var *lst, char *name);

//Exit
void checkExit(char *string);