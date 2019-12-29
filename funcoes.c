//INCLUDES
#include "funcoes.h"
#include "grammar.tab.h"

char *closePrograma = "termina";
char *path = "./exec/";

instrucao inst;

int informa(){
    printf("\nCOMMAND: %s",inst.command);
    for(int i = 0;i<inst.count;i++)
        printf("\nPARAM: %s",inst.param[i]);
    return 0;
}

int newInstrucao(){
    inst.count = 0;
    return 0;
}

void insertCommand(char *command){
    strcpy(inst.command, command);
}

void insertParam(char *param){
    strcpy(inst.param[inst.count++], param);
}

//Executa o comando encontrado
void execute(){
    printf("PASSOU");
    char *aux = strdup(path);
    strcat(aux,(inst).command);
    
    int nArgs = inst.count + 1; //Numero de elementos necessarios para o novo array
    char *array[nArgs];
    //
    array[0] = aux;
    for(int i = 0;i<nArgs;i++){
        array[i+1] = inst.param[i];
    }
    array[nArgs] = NULL;

    //criação de um processo filho
    int pid = fork();
    if(pid == 0)
        execvp(aux, array);
    else
        wait(NULL); //espera que o processo filho termine
}


//Verifica se existe o comando
//1 = encontrado
//0 = não encontrado
int existsCommand(){
    struct dirent *de;
    struct stat buf;
    DIR *dr = opendir(path);

    if (dr == NULL)  return 0; //Pasta não existe

    //Corre cada pasta/ficheiro encontrado
    while ((de = readdir(dr)) != NULL) {
        stat(de->d_name, &buf);
        if(strcmp(de->d_name,inst.command) == 0) //Compara para ver se existe o comando
            return 1;
    }
    return 0;
}
