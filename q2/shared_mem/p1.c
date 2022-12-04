#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>


#define MEMSIZE 50
#define READSIZE 5*sizeof(char)
#define ERR (char *)-1
#define LEN 7
#define ARRSIZE 50*sizeof(char *)


// convert int to string
void inttos(int n, char *out){
    char buff[5];
    int x = (int) '0';
    int i = 0;
    while (n>0){
        int a = n%10;
        buff[i] = (char) (a + x);
        i++;
        n = n/10;
    }
    buff[i] = '\0';

    char y[strlen(buff)];
    for(int i=0; i<strlen(buff); i++){
        y[strlen(y) - 1 - i] = buff[i];
    }

    strcpy(out,y);
}


// random string generator
char *randomString(int length){
    char *out = malloc((length+1)*sizeof(char)), *string = "abcdefghijklmnopqrstuvwxyz";
    int a = (int) 'a';

    for (int i=0; i<length; i++){
        int r = rand();
        r = r%26;
        out[i] = string[r];
    }

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
    // key = ftok("mem",100);
    key = 9876;

    shmid = shmget(key, MEMSIZE, 0666 | IPC_CREAT);

    if(shmid < 0){
        perror("p1 - shmget error");
        exit(EXIT_FAILURE);
    }

    wri = shmat(shmid, (void *)0, 0);

    if(wri == ERR){
        perror("p1 - shmat error");
        exit(EXIT_FAILURE);
    }

    
    int out = 0;
    
    while(out<50){
        
        // concat 5 strings from the array
        char write[50];
        int max;
        for(int i=0; i<5; i++){
            char buf[5];
            inttos(out+i,buf);
            strcat(write,buf);
            strcat(write,arr[out+i]);
            max = out+i;
        }

        int size = strlen(write);

        // write the concatenated string into the shared memory
        memcpy(wri,write,size * sizeof(char));

        pid_t pid = fork();

        if(pid<0){
            perror("p1 - fork error");
            exit(EXIT_FAILURE);
        }
        else if (pid==0){
            execl("./p2",NULL);
            exit(EXIT_SUCCESS);
        }
        else{
            wait(NULL);
	        tmp = wri;
            char high = *tmp;
            char hi = (char) ((int) '0' + max);
	        printf("%c\n",hi);
            if(high!=hi){
                printf("highest index received != highest index sent\n");
                exit(EXIT_FAILURE);
            }
            out = max;
        }
        out++;
        
    }

    tmp = wri;
    *wri = '0';
    
    return 0;

}
