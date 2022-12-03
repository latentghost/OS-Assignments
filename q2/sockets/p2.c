#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <string.h>
#include <unistd.h>


#define SIZE 5
#define LEN 7L
#define ARRSIZE 45*sizeof(char)
#define NAME "csock"


int d, c, s, r;
struct sockaddr_un addr;
socklen_t length;

int main(){

    char *arr = malloc(ARRSIZE);
    
    d = socket(AF_UNIX,SOCK_STREAM,0);
    if(d<0){
        perror("p2 - socket error");
        exit(EXIT_FAILURE);
    }

    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path,NAME);

    c = connect(d, (struct sockaddr *) &addr, SUN_LEN(&addr));
    if(c<0){
        perror("p2 - connect error");
        exit(EXIT_FAILURE);
    }

    //FILE *f = fdopen(d, "r+");

    r = recv(d, arr, sizeof(arr), 0);

    printf("%s\n",arr);

    close(d);

    unlink(NAME);

}
