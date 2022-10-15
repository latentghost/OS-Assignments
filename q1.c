#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


char *inp();
char **inp_split(char *inst);
int execute(char **comms);


char *commands[] = {"cd", "echo", "pwd"};


int func_cd(char **args){
    if(args[1]==NULL){
        printf("expected argument to cd")
    }
}


int main(){

    char *inst;
    char **comms;
    int status = 1;

    while(status){
        printf(">>> ");
        inst = inp();
        // comms = inp_split(inst);
        // status = execute(comms);
        printf("%s\n", inst);
    }
}


char *inp(){
    char *newi = NULL;
    size_t size = 0;
    int x = getline(&newi, &size, stdin);

    if(x==-1 && feof(stdin)){
        exit(EXIT_SUCCESS);
    }
    else if(x==-1){
        perror("instruction input");
        exit(EXIT_FAILURE);
    }

    return newi;

}


char **inp_split(char *inst){

}


int execute(char **comms){

}