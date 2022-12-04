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
    key = 2121;

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
        char *write = "";
        int max;
        for(int i=0; i<5; i++){
            char buf[2];
            char buff[1];
            if(out+i<10){
                buff[0] = (char) (out + i + 48);
                strcat(write,buff);
            }
            else{
                buf[1] = (char) ((out + i)%10 + 48);
                buf[0] = (char) ((out + i)/10 + 48);
                strcat(write,buf);
            }
            strcat(write,arr[out+i]);
            max = out+i;
        }

        int size = strlen(write);

        // write the concatenated string into the shared memory
        memset(read,'~',MEMSIZE*sizeof(char));
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
	        int high;
            if(*tmp=='~'){
                tmp++;
                high = ((int) *tmp - 48);
                tmp++;
            }
            else{
                int d1 = ((int) *tmp - 48) * 10;
                tmp++;
                int d2 = ((int) *tmp - 48);
                high = d1+d2;
                tmp++;
            }
            if(high!=max){
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
