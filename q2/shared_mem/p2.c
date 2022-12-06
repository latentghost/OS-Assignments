#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>


#define MEMSIZE 50
#define ERR (char *)-1
#define LEN 7
#define ARRSIZE 50*sizeof(char *)


int main(){

    // variable prototypes
    int key,shmid;
    char *read;

    // define and attach to the shared memory
    key = 2121;

    shmid = shmget(key, MEMSIZE, 0666);

    if(shmid < 0){
        perror("shmid error");
        exit(EXIT_FAILURE);
    }

    read = shmat(shmid, (void *)0, 0);

    if(read == ERR){
        perror("shmat error");
        exit(EXIT_FAILURE);
    }

    // read and print data from the shared memory 
    char *tmp = read;
    int max = 0;
    for(int j=0; j<5; j++){
        
        // print index
        int ind = (int) (*tmp);
        ind -= 48;
        tmp++;
        int j = (int) (*tmp);
        if(j>=48 && j<=57){
            ind *= 10;
            ind += j-48;
            tmp++;
        }

        printf("%i ",ind);

        // print the string
        for(int i=0; i<LEN; i++){
            printf("%c",*(tmp));
            tmp++;
        }

        // only store the last index
        if(ind>max) max = ind;
        printf("\n");
    }

    printf("\n");

    // return the highest index received to p1
    char outind[3];
    outind[2] = '\0';
    if(max<10){
        outind[0] = (char) (48 + max);
        outind[1] = '~';
    }
    else{
        outind[0] = (char) (48 + max/10);
        outind[1] = (char) (48 + max%10);
    }

    memset(read,'~',MEMSIZE*sizeof(char));
    memcpy(read,outind,strlen(outind)*sizeof(char));

    shmdt(read);

    return 0;

}
