#define ll long long

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <sched.h>

struct timespec s1,f1,s2,f2,s3,f3;


void *counta(void *i){

    struct sched_param p = {.sched_priority = -19};
    pthread_setschedparam(pthread_self(),SCHED_OTHER,&p);

    ll x = 1;
    ll r = x<<32;
    ll j = *((ll *) i);
    for(;j<=r;j++);

    return NULL;
}


void *countb(void *i){

    struct sched_param p = {.sched_priority = 20};
    pthread_setschedparam(pthread_self(),SCHED_FIFO,&p);

    ll x = 1;
    ll r = x<<32;
    ll j = *((ll *) i);
    for(;j<=r;j++);

    return NULL;
}


void *countc(void *i){

    struct sched_param p = {.sched_priority = 98};
    pthread_setschedparam(pthread_self(),SCHED_RR,&p);

    ll x = 1;
    ll r = x<<32;
    ll j = *((ll *) i);
    for(;j<=r;j++);

    return NULL;
}


int main(int argc, char* argv[]){
    
    pthread_t ta,tb,tc;
    ll i = 1;

    // Start all threads in parallel

    clock_gettime(CLOCK_REALTIME,&s1);

    pthread_create(&ta,NULL,&counta,&i);

    clock_gettime(CLOCK_REALTIME,&s2);

    pthread_create(&tb,NULL,&countb,&i);

    clock_gettime(CLOCK_REALTIME,&s3);

    pthread_create(&tc,NULL,&countc,&i);


    // End thread A

    pthread_join(ta,NULL);

    clock_gettime(CLOCK_REALTIME,&f1);
    
    ll s,ns;

    s = f1.tv_sec - s1.tv_sec;
    ns = f1.tv_nsec - s1.tv_nsec;
    if(ns<0){
        s--;
        ns += 1000000000L;
    }
    printf("SCHED_OTHER: %lli.%lli seconds\n",s,ns);


    // End thread B

    pthread_join(tb,NULL);

    clock_gettime(CLOCK_REALTIME,&f2);

    s = f2.tv_sec - s2.tv_sec;
    ns = f2.tv_nsec - s2.tv_nsec;
    if(ns<0){
        s--;
        ns += 1000000000L;
    }
    printf("SCHED_FIFO: %lli.%lli seconds\n",s,ns);


    // End thread C

    pthread_join(tc,NULL);

    clock_gettime(CLOCK_REALTIME,&f3);

    s = f3.tv_sec - s3.tv_sec;
    ns = f3.tv_nsec - s3.tv_nsec;
    if(ns<0){
        s--;
        ns += 1000000000L;
    }
    printf("SCHED_RR: %lli.%lli seconds\n",s,ns);


    return 0;

}
