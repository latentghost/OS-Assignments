#include<stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>


int main(){
    pid_t pid = fork();

    if(pid==0){
        sleep(1);
        execlp("p2", NULL);
	exit(1);
    }
    else{
        execlp("p1", NULL);
	exit(1);
        // wait(NULL);
    }
}
