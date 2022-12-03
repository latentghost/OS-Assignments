#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>


#define COPYSIZE 5*sizeof(char *)
#define ERR (char *)-1
#define LEN 7
#define ARRSIZE 50*sizeof(char *)


int main(){

    // variable prototypes
    int key,shmid;
    char *read, *tmp;

    // define and attach to the shared memory
    key = ftok("mem",100);

    shmid = shmget(key, COPYSIZE, 0666);

    if(shmid < 0){
        perror("shmid error");
        exit(EXIT_FAILURE);
    }

    read = shmat(shmid, (void *)0, 0);

    if(read == ERR){
        perror("shmat error");
        exit(EXIT_FAILURE);
    }

    // read data from the shared memory
    for(tmp = read; *tmp != '-'; tmp += 1){
         printf("%c",*tmp);
    }

    printf("\n");

    *tmp = '~';
    
    return 0;

}