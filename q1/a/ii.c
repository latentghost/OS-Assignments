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


// forks (global variables)
ll used[5];
sem_t forks[5];



// eat function
void f1(int ind){

    int i = ind, j = (ind+1)%5;

    // wait for semaphore to be freed
    sem_wait(&forks[i]);
    sem_wait(&forks[j]);

    // eat
    sleep(1);
    printf("Philosopher %i is eating\n",i);

    // free the semaphore
    sem_post(&forks[j]);
    sem_post(&forks[i]);

    used[i]++;

}

// think function
void f2(void *ind){
    int i = (int *) ind;
    sleep(1);
    printf("Philosopher %i is thinking\n",i);
    return;
}


int main(){

    pthread_t phils[NUM];

    // initialise the binary semaphores
    fr(i,0,5){
        sem_init(&forks[i],0,0);
    }

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

    // destroy the binary semaphores
    fr(i,0,5){
        sem_destroy(&forks[i]);
    }

    fr(i,0,5)
        printf("%i %lli\n",i, used[i]);
}