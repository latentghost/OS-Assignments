#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void do_rm(char *file, char *op){
    char c[2];
    if(op==NULL){
        if(remove(file)!=0){
            perror("no such file or directory");
            exit(EXIT_FAILURE);
        }
    }
    else if(strcmp(op,"-i")==0){
        printf("Do you wish to delete %s? (y/n) ",file);
        scanf("%s", c);

        if(strcmp(c,"n")!=0 && strcmp(c,"y")!=0){
            printf("Invalid response");
            exit(EXIT_FAILURE);
        }
        if(strcmp(c,"n")==0) exit(EXIT_SUCCESS);
        if(remove(file)!=0){
            perror("no such file or directory");
            exit(EXIT_FAILURE);
        }
    }
    else if(strcmp(op,"-v")==0){
        
        if(remove(file)!=0){
            perror("no such file or directory");
            exit(EXIT_FAILURE);
        }
        printf("%s\n",file);
    }
}


int main(int argc, char *argv[]){
    if(argv[1]==NULL){
        perror("expected argument to rm");
    }

    else if(argv[1][0]=='-'){
        do_rm(argv[2],argv[1]);
    }

    else{
        do_rm(argv[1],NULL);
    }
}