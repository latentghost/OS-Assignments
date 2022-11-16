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
        execl("/bin/bash","sh","script.sh",(char *) NULL);

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
            execl("/bin/bash","sh","script.sh",(char *) NULL);

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
                execl("/bin/bash","sh","script.sh",(char *) NULL);

                exit(EXIT_SUCCESS);
            }

            else{
		wait(NULL);
                //do {pid3 = wait(&status3);}
                //while(!WIFEXITED(status3) && !WIFSIGNALED(status3));

                clock_gettime(CLOCK_REALTIME, &f3);
            }
	    wait(NULL);

            //do {pid2 = wait(&status2);}
            //while(!WIFEXITED(status2) && !WIFSIGNALED(status2));

            clock_gettime(CLOCK_REALTIME, &f2);
        }
        
	wait(NULL);
        //do {pid1 = wait(&status1);}
        //while(!WIFEXITED(status1) && !WIFSIGNALED(status1));

        clock_gettime(CLOCK_REALTIME, &f1);
    }


    
}
