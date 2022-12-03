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

    strcpy(out,buff);
}


int main(){

    // variable prototypes
    int key,shmid;
    char *read, *tmp;

    // define and attach to the shared memory
    key = ftok("mem",100);

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
    while(*read != '0'){   
        tmp = read;
        int max = 0;
        while(*tmp!='-'){
            
            // print index
            int i = 1, ind = 0;
            while(((int) (*tmp - '0')) < 10){
                printf("%c",*tmp);
                ind += ((int) (*tmp - '0'))*i;
                i*=10;
                tmp++;
            }

            printf(" ");

            // print the string
            for(int i=0; i<LEN; i++){
                printf("%c",*(tmp+i));
            }
            tmp += LEN;

            // only store the last index
            if(ind>max) max = ind;

            printf("\n");
        }

        // return the highest index received to p1
        char end[5] = "~";
	char outind[5];
        inttos(max, outind);
        strcat(end,outind);

        memcpy(read,end,strlen(end)*sizeof(char));

        while(*read == '~'){
            sleep(1);
        }
    }
    
    return 0;

}
