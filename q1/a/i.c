#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


#define NUM 5
#define ui unsigned int
#define ll long long
#define fr(a,b,c) for(int a=b; a<c; a++)
#define ITERS 1234


typedef struct lock{
    int aval;
}lock;


// forks (global variables)
lock forks[5];
int mutex = 0;
ll used[5];


// eat function
void f1(int ind){

    int i = ind, j = (i+1)%5;

    // wait for the lock to be freed
    while(mutex!=i);
    while(forks[i].aval==0 && forks[j].aval==0);

    // lock the forks
    forks[i].aval = 0;
    forks[j].aval = 0;

    // eat
    usleep(500000);
    printf("Philosopher %i is eating\n",i);

    // free the lock
    forks[i].aval = 1;
    forks[j].aval = 1;

    mutex = (i+1)%5;

}



int main(){

    pthread_t phils[NUM];

    fr(i,0,5)
        forks[i].aval = 1;

    fr(j,0,ITERS){

        fr(i,0,5){
            // eat function called
            if(pthread_create(&phils[i],NULL,(void *)f1,(int *) i)){
                perror("pthread_create error");
                exit(EXIT_FAILURE);
            }
        }

        // join threads
        fr(i,0,5){
            if(pthread_join(phils[i],NULL)){
                perror("pthread_join error");
                exit(EXIT_FAILURE);
            }
        }
    }

    fr(i,0,5)
        printf("%i %lli\n",i, used[i]);
}