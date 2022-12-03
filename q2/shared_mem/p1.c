#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <math.h>


#define COPYSIZE 5*sizeof(char *)
#define ERR (char *)-1
#define LEN 7
#define ARRSIZE 50*sizeof(char *)


// random string generator
char *randomString(int length){
    char *out = malloc((length+1)*sizeof(char)), *string = "abcdefghijklmnopqrstuvwxyz";
    int a = (int) 'a';

    for (int i=0; i<length; i++){
        int r = rand();
        r = r%26;
        out[i] = string[r];
    }
    out[length] = '\0';

    return out;
}


int main(){

    // variable prototypes
    int key,shmid;
    char *wri, *tmp;
    char **arr = (char **) malloc(ARRSIZE);

    // populate array
    for (int i=0; i<50; i++){
        arr[i] = randomString(LEN);
    }

    // define and attach to the shared memory
    key = 101;

    shmid = shmget(key, COPYSIZE, 0666 | IPC_CREAT);

    if(shmid < 0){
        perror("shmid error");
        exit(EXIT_FAILURE);
    }

    wri = shmat(shmid, (void *)0, 0);

    if(wri == ERR){
        perror("shmat error");
        exit(EXIT_FAILURE);
    }

    
    int out = 1;
    
    while(out<=50){

        // concat 5 strings from the array
        char *copy = "";
        for(int i=0; i<5; i++){
            char buf[10];
            itoa(out+i,buf,10);
            strcat(copy,buf);
            strcat(copy,arr[i]);
        }

        // write the concatenated string into the shared memory
        memcpy(wri,copy,COPYSIZE);
        tmp = wri;
        tmp += COPYSIZE;

        // denotes the end of the segment
        *tmp = '-';

        // wait for the consumer to read the shared memory
        while(*wri != '~'){
            sleep(1);
        }
    }
    
    return 0;

}