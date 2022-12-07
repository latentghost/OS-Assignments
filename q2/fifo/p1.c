#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>


#define NAME "./ofif"
#define READSIZE 3*sizeof(char)
#define SENDSIZE 100*sizeof(char)
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
    
    char **arr = (char **) malloc(ARRSIZE);

    int f, r, out;
    char rd[3];

    // populate array
    for (int i=0; i<50; i++){
        arr[i] = randomString(LEN);
    }

    mkfifo(NAME, 0666);

    out = 0;

    while(out < 50){

        f = open(NAME, O_WRONLY);

        char *data = malloc(SENDSIZE);
        int max;
        for(int i=0; i<5; i++){
            char buf[3];
            char buff[2];
            if(out+i<10){
                buff[0] = (char) (out + i + 48);
                strcat(data,buff);
            }
            else{
                buf[1] = (char) ((out + i)%10 + 48);
                buf[0] = (char) ((out + i)/10 + 48);
                strcat(data,buf);
            }

            strcat(data,arr[out+i]);
            max = out+i;

        }

        int size = strlen(data);

        write(f, data, size+1);

        close(f);

        // pid_t pid = fork();

        // if(pid<0){
        //     perror("p1 - fork error");
        //     exit(EXIT_FAILURE);
        // }
        // else if(pid==0){
        //     execl("./p2",NULL);
        //     exit(EXIT_SUCCESS);
        // }
        // else{
        //     wait(NULL);
        f = open(NAME, O_RDONLY);

        r = read(f,rd,sizeof(rd));

        char *t = rd;
        int ind = (int) (*t);
        ind -= 48;
        t++;
        int j = (int) (*t);
        if(j>=48 && j<=57){
            ind *= 10;
            ind += j-48;
        }

        if(ind!=max){
            printf("%i %i\n",ind,max);
            printf("highest index received != highest index sent\n");
            exit(EXIT_FAILURE);
        }
        out = max;
        // }

        printf("%i %i\n",out,max);

        close(f);

        out++;
    }

    return 0;

}