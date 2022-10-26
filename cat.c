#include <stdio.h>
#include <stdlib.h>
#include <string.h>




int main(int argc, char *argv[]){
    if(argc==1){
        perror("expected argument to cat");
        exit(EXIT_FAILURE);
    }

    else if(argv[1][0]=='-'){
        if(strcmp(argv[1],"-n")==0){

            FILE *f = fopen(argv[2],"r");
            if(f==NULL){
                perror("Unable to open file");
                exit(EXIT_FAILURE);
            }

            char c;
            int i = 1;
            printf("%i  ",i);
            i++;
            while((c=fgetc(f))!=EOF){
                printf("%c",c);
                if(c=='\n'){
                    printf("%i  ", i);
                    i++;
                }
            }
            printf("\n");

            fclose(f);
        }

        else if(strcmp(argv[1],"-b")==0){
            
            FILE *f = fopen(argv[2],"r");
            if(f==NULL){
                perror("Unable to open file");
                exit(EXIT_FAILURE);
            }

            char c,prev='?';
            int i = 1;
            while((c=fgetc(f))!=EOF){
                if(prev=='?'){
                    if(c=='\n'){
                        printf("%c",c);
                    }
                    else{
                        printf("%i  ",i);
                        i++;
                        printf("%c",c);
                    }
                    prev = c;
                    continue;
                }
                else if(prev=='\n' && c!='\n'){
                    printf("%i  ", i);
                    i++;
                }
                printf("%c",c);
                prev = c;
            }

            printf("\n");

            fclose(f);
        }
    }

    else {

        FILE *f = fopen(argv[1],"r");
        if(f==NULL){
            perror("Unable to open file");
            exit(EXIT_FAILURE);
        }

        char c;
        while((c=fgetc(f))!=EOF){
            printf("%c",c);
        }
        printf("\n");

        fclose(f);
    }
}