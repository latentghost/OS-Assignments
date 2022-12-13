#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>


#define NUM 5
#define ui unsigned int
#define ll long long
#define fr(a,b,c) for(int a=b; a<c; a++)
#define ITERS 1234


// philosophers (threads) and picks (global variables)
pthread_mutex_t lock;
ll used[5];



// eat function
void f1(int ind){

    int i = ind, j = (i+1)%5;
    pthread_mutex_lock(&lock);

    usleep(50);
    used[i]++;

    pthread_mutex_unlock(&lock);

}

// think function
void f2(void *ind){
    usleep(5);
    return;
}


int main(){

    pthread_t phils[NUM];

    pthread_mutex_init(&lock,NULL);

    fr(j,0,ITERS){

        fr(i,0,5){
            // eat
            if(pthread_create(&phils[i],NULL,(void *)f1,(int *) i)){
                perror("pthread_create error");
                exit(EXIT_FAILURE);
            }
            //think
            if(pthread_create(&phils[i],NULL,(void *)f2,(int *) i)){
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

    // pthread_mutex_destroy(&stop);
    pthread_mutex_destroy(&lock);

    fr(i,0,5)
        printf("%i %lli\n",i, used[i]);
}