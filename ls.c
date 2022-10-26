#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>



void do_ls(char *dir, char *op){

    DIR *curr = opendir(dir);

    if(curr==NULL){
        perror("Directory not readable");
        exit(EXIT_FAILURE);
    }

    if(op==NULL){

        struct dirent *dent;
        while((dent = readdir(curr))!=NULL){
            if(dent->d_name[0]!='.'){
                printf("%s  ", dent->d_name);
            }
        }
        printf("\n");

        return;

    }

    else if(strcmp(op,"-a")==0){

        struct dirent *dent;
        while((dent = readdir(curr))!=NULL){
            printf("%s  ", dent->d_name);
        }
        printf("\n");

        return;
    }

    else if(strcmp(op, "-r")==0){
        struct dirent *dent;
        int size = 64, pos = 0;
        char **out = malloc(size*sizeof(char *));

        while((dent = readdir(curr))!=NULL){
            if(dent->d_name[0]!='.'){
                out[pos] = dent->d_name;
                pos++;
            }
            if(pos>size){
                out = realloc(out, (size+64)*sizeof(char *));
                size += 64;
            }
        }

        while(pos>0){
            printf("%s  ", out[pos-1]);
            pos--;
        }
        printf("\n");
    }
}



int main(int argc, char *argv[]){
    if(argc==1){
        do_ls(".", NULL);
    }

    else{
        if(argv[1][0]=='-'){
            if(argc==2){
                do_ls(".",argv[1]);
            }
            else{
                do_ls(argv[2],argv[1]);
            }
        }
        else{
            do_ls(argv[1],NULL);
        }
    }
}