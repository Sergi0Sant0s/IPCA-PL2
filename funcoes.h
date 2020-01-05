
typedef struct _text{
    char *value;
    int type; //TXT | VAR
    struct _text *child;
}Text;

typedef struct _var{
    char *name;
    char *value;
    struct _var *next;
}Var;

typedef struct _command{
    char *command;
    struct _text *list;
}Command;

typedef struct _ciclo{
    char *varname;
    Text *folder;
    struct _instrucao *list;
}Ciclo;

typedef struct _instrucao{
    void *value;
    int type; //CMD | CICLO
    struct _instrucao *child;
}Instrucao;

#define CICLO 50    //TYPE DA STRUCT INSTRUCAO
#define CMD 51  //TYPE DA STRUCT INSTRUCAO
#define VAR 52      //TYPE DA STRUCT TEXT
#define TXT 53     //TYPE DA STRUCT TEXT

//Funcoes
void yyerror(char *c);
int yylex(void);

//EXEC
int existsCommand(char *command);
Text* getContainerFolder(char* folder);
void execute(char *command, char **array);
int executaCommand(Command *aux);
int commandAcrescenta(Command* aux);
int executaInstrucao(Instrucao *inst);

//Armazenamento de Texts
Text* newText(char *string, int type);
Text* insertText(Text *lst, Text *temp);
void printTexts(Text *lst);
int countText(Text *lst);

//Variables
Var* newVariable(char* name, char* value);
Var* editVariable(char *name, char *value);
Var* returnValue(char *varname);

//COMMANDS
Command* newCommand(char* command, Text* list);

//CICLOS
Ciclo* newCiclo(char* varname, Text* folder, Instrucao *list);
void executaCiclo(Ciclo* temp);

//Instrucao
Instrucao* insertInstrucao(Instrucao *lst, Instrucao *last);
Instrucao* newInstrucao(void *value, int type);

//Exit
void termina();