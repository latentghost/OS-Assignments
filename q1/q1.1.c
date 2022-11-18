#define ll long long

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <sched.h>


void *counta(void *i){

    struct timespec st,fin;
    clock_gettime(CLOCK_REALTIME,&st);

    struct sched_param p = {.sched_priority = -19};
    pthread_setschedparam(pthread_self(),SCHED_OTHER,&p);

    ll x = 1;
    ll r = x<<32;
    ll j = *((ll *) i);
    for(;j<=r;j++);

    clock_gettime(CLOCK_REALTIME,&fin);

    ll s = fin.tv_sec - st.tv_sec;
    ll ns = fin.tv_nsec - st.tv_nsec;

    if(ns<0){
        s--;
        ns += 1000000000L;
    }

    printf("SCHED_OTHER: %lli.%lli secs\n",s,ns);

    return NULL;
}


void *countb(void *i){

    struct timespec st,fin;
    clock_gettime(CLOCK_REALTIME,&st);

    struct sched_param p = {.sched_priority = 20};
    pthread_setschedparam(pthread_self(),SCHED_FIFO,&p);

    ll x = 1;
    ll r = x<<32;
    ll j = *((ll *) i);
    for(;j<=r;j++);

    clock_gettime(CLOCK_REALTIME,&fin);

    ll s = fin.tv_sec - st.tv_sec;
    ll ns = fin.tv_nsec - st.tv_nsec;

    if(ns<0){
        s--;
        ns += 1000000000L;
    }

    printf("SCHED_FIFO: %lli.%lli secs\n",s,ns);

    return NULL;
}


void *countc(void *i){

    struct timespec st,fin;
    clock_gettime(CLOCK_REALTIME,&st);

    struct sched_param p = {.sched_priority = 98};
    pthread_setschedparam(pthread_self(),SCHED_RR,&p);

    ll x = 1;
    ll r = x<<32;
    ll j = *((ll *) i);
    for(;j<=r;j++);

    clock_gettime(CLOCK_REALTIME,&fin);

    ll s = fin.tv_sec - st.tv_sec;
    ll ns = fin.tv_nsec - st.tv_nsec;

    if(ns<0){
        s--;
        ns += 1000000000L;
    }

    printf("SCHED_RR: %lli.%lli secs\n",s,ns);

    return NULL;
}


int main(int argc, char* argv[]){
    
    pthread_t ta,tb,tc;
    ll i = 1;

    pthread_create(&ta,NULL,&counta,&i);

    pthread_join(ta,NULL);

    pthread_create(&tb,NULL,&countb,&i);

    pthread_join(tb,NULL);

    pthread_create(&tc,NULL,&countc,&i);

    pthread_join(tc,NULL);

    return 0;

}
