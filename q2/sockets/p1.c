#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <string.h>
#include <unistd.h>


#define SIZE 5
#define LEN 7L
#define ARRSIZE 50*sizeof(char *)
#define NAME "p1socket"


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


int d, b, l, c, s;
int p2s;
struct sockaddr addr, p2addr;
socklen_t length, p2length;

int main(){

    char **arr = (char **) malloc(ARRSIZE);

    // populate array
    for (int i=0; i<50; i++){
        arr[i] = randomString(LEN);
    }
    
    d = socket(AF_UNIX,SOCK_STREAM,0);
    if(d<0){
        perror("p1 - socket error");
        exit(EXIT_FAILURE);
    }

    addr.sa_family = AF_UNIX;
    strcpy(addr.sa_data,NAME);

    length = strlen(NAME) + sizeof(AF_UNIX);

    b = bind(d, &addr, length);
    if(b<0){
        perror("p1 - bind error");
        exit(EXIT_FAILURE);
    }

    l = listen(d, 1);
    if(l<0){
        perror("p1 - listen error");
        exit(EXIT_FAILURE);
    }

    p2s = accept(d, &p2addr, &p2length);
    if(p2s<0){
        perror("p1 - accept error");
        exit(EXIT_FAILURE);
    }

    FILE *f = fdopen(p2s, "r+");

    for(int i=0; i<SIZE; i++){
        s = send(p2s, arr[i], LEN, 0);
    }

    close(d);

}