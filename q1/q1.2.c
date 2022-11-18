#define ll long long

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>


struct timespec s1,f1,s2,f2,s3,f3;


int main(int argc, char *argv[]){

    pid_t pid1, status1;

    clock_gettime(CLOCK_REALTIME, &s1);

    pid1 = fork();

    if(pid1<0){
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    else if(pid1==0){
        execl("/bin/bash","sh","s1.sh",(char *) NULL);

        exit(EXIT_SUCCESS);
    }

    else{

        pid_t pid2, status2;

        clock_gettime(CLOCK_REALTIME, &s2);

        pid2 = fork();

        if(pid2<0){
            perror("Fork failed");
            exit(EXIT_FAILURE);
        }

        else if(pid2==0){
            execl("/bin/bash","sh","s2.sh",(char *) NULL);

            exit(EXIT_SUCCESS);
        }

        else{

            pid_t pid3, status3;

            clock_gettime(CLOCK_REALTIME, &s3);

            pid3 = fork();

            if(pid3<0){
                perror("Fork failed");
                exit(EXIT_FAILURE);
            }

            else if(pid3==0){
                execl("/bin/bash","sh","s3.sh",(char *) NULL);

                exit(EXIT_SUCCESS);
            }

            else{
                wait(NULL);
                clock_gettime(CLOCK_REALTIME, &f3);
            }

            wait(NULL);
            clock_gettime(CLOCK_REALTIME, &f2);
        }
        
        wait(NULL);
        clock_gettime(CLOCK_REALTIME, &f1);
    }

    ll s,ns;
    s = f1.tv_sec - s1.tv_sec;
    ns = f1.tv_nsec - s1.tv_nsec;
    if(ns < 0L){
        s--;
        ns += 1000000000L;
    }
    printf("Child process 1: %lli.%lli seconds\n",s,ns);

    s = f2.tv_sec - s2.tv_sec;
    ns = f2.tv_nsec - s2.tv_nsec;
    if(ns < 0L){
        s--;
        ns += 1000000000L;
    }
    printf("Child process 2: %lli.%lli seconds\n",s,ns);

    s = f3.tv_sec - s3.tv_sec;
    ns = f3.tv_nsec - s3.tv_nsec;
    if(ns < 0L){
        s--;
        ns += 1000000000L;
    }
    printf("Child process 3: %lli.%lli seconds\n",s,ns);
    
}
