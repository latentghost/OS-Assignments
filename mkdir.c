#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>


void do_mkdir(char *dirname, char *op){
    if(op==NULL){
        if(mkdir(dirname,0777)==-1){
            perror("mkdir error");
        }
    }

    else if(strcmp(op,"-v")==0){
        if(mkdir(dirname,0777)==-1){
            perror("mkdir error");
            exit(EXIT_FAILURE);
        }
        printf("%s\n",dirname);
    }

    else if(strcmp(op,"-p")==0){
        char *delim = "/";
        char *token = strtok(dirname,delim);
        while(1){
            if(token==NULL) break;
            if(mkdir(token,0777)==-1){
                perror("mkdir error");
                exit(EXIT_FAILURE);
            }
            if(chdir(token)!=0){
                perror("shell error");
                exit(EXIT_FAILURE);
            }
            token = strtok(NULL,delim);
        }
    }
}


int main(int argc, char *argv[]){
    if(argc==1){
        perror("expected argument to mkdir");
        exit(EXIT_FAILURE);
    }

    if(argv[1][0]=='-'){
        do_mkdir(argv[2],argv[1]);
    }
    else do_mkdir(argv[1],NULL);

    return 1;
}