#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>


#define NUM 5
#define ui unsigned int
#define ll long long
#define fr(a,b,c) for(int a=b; a<c; a++)


// philosophers (threads) and picks (global variables)
pthread_mutex_t picks[5];
ll used[5];


// sleep in milliseconds
int msleep(ui n){ return usleep(n*1000); }


// thread function
void f1(int ind){

    int i = ind, j = (i+1)%5;
    pthread_mutex_lock(&picks[i]);
    pthread_mutex_lock(&picks[j]);

    usleep(50);
    used[i]++;

    pthread_mutex_unlock(&picks[i]);
    pthread_mutex_unlock(&picks[j]);

}

void f2(void *ind){
    usleep(5);
    return;
}


int main(){

    pthread_t phils[NUM];

    fr(i,0,5){
        pthread_mutex_init(&picks[i],NULL);
        used[i] = 0L;
    }

    fr(j,0,396){

        fr(i,0,5){
            if(pthread_create(&phils[i],NULL,(void *)f1,(int *) i)){
                perror("pthread_create error");
                exit(EXIT_FAILURE);
            }
            if(pthread_create(&phils[i],NULL,(void *)f2,(int *) i)){
                perror("pthread_create error");
                exit(EXIT_FAILURE);
            }
        }

        fr(i,0,5){
            if(pthread_join(phils[i],NULL)){
                perror("pthread_join error");
                exit(EXIT_FAILURE);
            }
        }
    }

    // pthread_mutex_destroy(&stop);
    fr(i,0,5)
        pthread_mutex_destroy(&picks[i]);

    fr(i,0,5)
        printf("%i %lli\n",i, used[i]);
}