#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


void do_date(char *op){
    time_t currtime = time(NULL);
    struct tm *tpr = localtime(&currtime);

    char out[256] = {0};
    memset(out,0,256);

    if(op==NULL || strcmp(op,"-n")==0){
        strftime(out, 256, "%a %b %d %H:%M:%S %Z %Y",tpr);
        puts(out);
    }
    else if(strcmp(op,"-R")==0){
        strftime(out, 256, "%a, %d %b %Y %H:%M:%S %z",tpr);
        puts(out);
    }
    else{
        perror("date error");
        exit(EXIT_FAILURE);
    }
}


int main(int argc, char *argv[]){
    do_date(argv[1]);
}