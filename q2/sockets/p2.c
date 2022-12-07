#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <string.h>
#include <unistd.h>


#define SIZE 5
#define LEN 7
#define ARRSIZE 45*sizeof(char)
#define SENDSIZE 100*sizeof(char)
#define NAME "csock"


int d, b, c, s, r;
struct sockaddr_un addr;
socklen_t length;

int main(){

    char *arr = malloc(SENDSIZE);
    
    d = socket(AF_UNIX,SOCK_STREAM,0);
    if(d<0){
        perror("p2 - socket error");
        exit(EXIT_FAILURE);
    }

    // memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path,NAME);

    length = strlen(addr.sun_path) + sizeof(addr.sun_family);

    c = connect(d, (struct sockaddr *) &addr, SUN_LEN(&addr));
    if(c<0){
        perror("p2 - connect error");
        exit(EXIT_FAILURE);
    }

    int min = -1;

    // while(min<50){

        r = recv(d, arr, SENDSIZE, 0);

        char *tmp = arr;

        for(int i=0; i<SIZE; i++){
            int in = 0;

            in += *tmp - '0';
            tmp++;
            if(*tmp>=48 && *tmp<=57){
                in *= 10;
                in += *tmp - '0';
                tmp++;
            }

            printf("%i ",in);

            for(int j=0; j<LEN; j++){
                printf("%c",*(tmp));
                tmp++;
            }

            printf("\n");

            if(in>min) min = in;
        }

        char snd[3];
        snd[2] = '~';

        if(min<10){
            snd[1] = '~';
            snd[0] = (char) (min + 48);
        }
        else{
            snd[1] = (char) (min%10 + 48);
            snd[0] = (char) (min/10 + 48);
        }

        s = send(d, snd, strlen(snd), 0);

    // }

    close(d);
    // unlink(NAME);

    return 0;

}