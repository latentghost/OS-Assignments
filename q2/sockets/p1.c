#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include <time.h>


#define LEN 7
#define ARRSIZE 50*sizeof(char *)
#define SENDSIZE 100*sizeof(char)
#define RECSIZE 3*sizeof(char)
#define NAME "csock"
#define fr(i,a,b) for(int i=a; i<b; i++)
#define ll long long


struct timespec start,fin;


// random string generator
char *randomString(int length){
    char *out = malloc((length+1)*sizeof(char)), *string = "abcdefghijklmnopqrstuvwxyz";
    int a = (int) 'a';

    fr(i,0,length){
        int r = rand();
        r = r%26;
        out[i] = string[r];
    }

    return out;
}


int d, b, l, c, s, r;
int p2s;
struct sockaddr_un addr, newaddr;
socklen_t length, newlen;

int main(int argc, char *argv[]){

    char **arr = (char **) malloc(ARRSIZE);

    // populate array
    fr(i,0,50){
        arr[i] = randomString(LEN);
    }

    d = socket(AF_UNIX,SOCK_STREAM,0);
    if(d<0){
        perror("p1 - socket error");
        exit(EXIT_FAILURE);
    }
    unlink(NAME);

    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path,NAME);

    b = bind(d, (struct sockaddr *) &addr, SUN_LEN(&addr));
    if(b<0){
        perror("p1 - bind error");
        exit(EXIT_FAILURE);
    }

    l = listen(d, 5);
    if(l<0){
        perror("p1 - listen error");
        exit(EXIT_FAILURE);
    }

    // send and receive data
    int out = 0;

    clock_gettime(CLOCK_REALTIME,&start);
    
    while(out<50){

        pid_t pid = fork();

        if(pid<0){
            perror("p1 - fork error");
            exit(EXIT_FAILURE);
        }
        else if(pid==0){
            execl("./p2s",NULL);
            exit(EXIT_SUCCESS);
        }
        else{
            p2s = accept(d, NULL, NULL);
            if(p2s<0){
                perror("p1 - accept error");
                exit(EXIT_FAILURE);
            }

            char *data = malloc(SENDSIZE);
            size_t len = 0;
            int max = -1;
            fr(i,0,5){
                char buf[3];
                char buff[2];
                if(out+i<10){
                    buff[0] = (char) (out + i + 48);
                    buff[1] = '\0';
                    strcat(data,buff);
                    len += strlen(buff);
                }
                else{
                    buf[1] = (char) ((out + i)%10 + 48);
                    buf[0] = (char) ((out + i)/10 + 48);
                    buf[2] = '\0';
                    strcat(data,buf);
                    len += strlen(buf);
                }
                strcat(data,arr[out+i]);
                len += strlen(arr[out+i]);
                if(out+i>max) max = out+i;
            }

            s = send(p2s, data, len, 0);

            wait(NULL);

            char *returnind = malloc(RECSIZE);
            size_t slen = 3;
            r = recv(p2s, returnind, slen, 0);

            // check highest index sent = highest index received
            char *tmp = returnind;
            int ind = (int) (*tmp);
            ind -= 48;
            tmp++;
            int j = (int) (*tmp);
            if(j>=48 && j<=57){
                ind *= 10;
                ind += j-48;
            }

            if(max!=ind){
                printf("highest index received != highest index sent\n");
                exit(EXIT_FAILURE);
            }
            out = max;

            out++;
        }

    }

    close(d);
    unlink(NAME);

    clock_gettime(CLOCK_REALTIME,&fin);

    ll s,ns;
    s = fin.tv_sec - start.tv_sec;
    ns = fin.tv_nsec - start.tv_nsec;
    if(ns<0){
        s--;
        ns += 1000000000L;
    }

    printf("SHARED MEMORY: %lli.%lli seconds\n",s,ns);
    
    return 0;

}
