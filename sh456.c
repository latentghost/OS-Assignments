#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Prototypes & Variable Declarations

void memerror(char **l){
    if(!l){
        fprintf(stderr, "memory allocation error\n");
        exit(EXIT_FAILURE);
    }
}


char *inst;
char **comms;
int status;
unsigned long size;
int n;
int next;
char *inp();
char **inp_split(char *inst);
int execute(char **comms);
int fork_execute(char **args);
int thread_execute(char *args);


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Internal commands

int func_pwd(char **args){
    if(args[1]==NULL || strcmp(args[1],"-L")==0 || strcmp(args[1],"-P")==0){
        char pwd[1024];
        getcwd(pwd,sizeof(pwd));
        printf("%s\n", pwd);
        return 1;
    }
    else{
        perror("Unsupported option type");
    }
    return 0;
}


int func_cd(char **args){
    if(args[1]==NULL || *args[1]=='~'){
        chdir(getenv("HOME"));
    }
    else if(*args[1]=='-'){
        if(chdir("..")!=0){
            perror("shell error");
        }
    }
    else{
        if(chdir(args[1])!=0){
            perror("shell error");
        }
    }
    return 1;
}


int func_echo(char **args){
    if(args[1]==NULL){
        perror("expected argument to echo");
    }
    else if(strcmp(args[1],"-n")==0){
        int i = 2;
        while(args[i]!=NULL){
            printf("%s ", args[i]);
            i++;
        }
    }
    else if(strcmp(args[1],"-E")==0){
        int i = 2;
        while(args[i]!=NULL){
            printf("%s ", args[i]);
            i++;
        }
        printf("\n");
    }
    else{
        int i = 1;
        while(args[i]!=NULL){
            printf("%s ", args[i]);
            i++;
        }
        printf("\n");
    }

    return 1;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// External commands

int fork_ls(char **args){

    int pid, status;

    pid = fork();

    if(pid<0){
        perror("Fork failed");
    }
    else if(pid==0){
        if(execv("/Users/akshatgupta/Desktop/IIITD/SEM_3/OS/os_assignments/ls", args)==-1){
            perror("shell error");
        }
        exit(EXIT_FAILURE);
    }
    else{
        do{pid = wait(&status);}
        while(!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}


int fork_cat(char **args){

    int pid, status;

    pid = fork();

    if(pid<0){
        perror("Fork failed");
    }
    else if(pid==0){
        if(execv("/Users/akshatgupta/Desktop/IIITD/SEM_3/OS/os_assignments/cat", args)==-1){
            perror("shell error");
        }
        exit(EXIT_FAILURE);
    }
    else{
        do{pid = wait(&status);}
        while(!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}


int fork_date(char **args){

    int pid, status;

    pid = fork();

    if(pid<0){
        perror("Fork failed");
    }
    else if(pid==0){
        if(execv("/Users/akshatgupta/Desktop/IIITD/SEM_3/OS/os_assignments/date", args)==-1){
            perror("shell error");
        }
        exit(EXIT_FAILURE);
    }
    else{
        do{pid = wait(&status);}
        while(!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}


int fork_rm(char **args){

    int pid, status;

    pid = fork();

    if(pid<0){
        perror("Fork failed");
    }
    else if(pid==0){
        if(execv("/Users/akshatgupta/Desktop/IIITD/SEM_3/OS/os_assignments/rm", args)==-1){
            perror("shell error");
        }
        exit(EXIT_FAILURE);
    }
    else{
        do{pid = wait(&status);}
        while(!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}


int fork_mkdir(char **args){

    int pid, status;

    pid = fork();

    if(pid<0){
        perror("Fork failed");
    }
    else if(pid==0){
        if(execv("/Users/akshatgupta/Desktop/IIITD/SEM_3/OS/os_assignments/mkdir", args)==-1){
            perror("shell error");
        }
        exit(EXIT_FAILURE);
    }
    else{
        do{pid = wait(&status);}
        while(!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Thread Execution - System call

void *sys_call(void *args){

    system(args);

    pthread_exit(NULL);

}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int main(){

    status = 1;

    while(status){
        printf("sh456 >>> ");
        inst = inp();
        comms = inp_split(inst);
        status = execute(comms);
    }
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Reading input and Parsing and Execute Call

char *inp(){
    char *newi = NULL;
    size = 0;
    n = getline(&newi, &size, stdin);
    newi[n-1] = '\0';

    if(n==-1 && feof(stdin)){
        exit(EXIT_SUCCESS);
    }
    else if(n==-1){
        perror("instruction input");
        exit(EXIT_FAILURE);
    }

    return newi;
}


char **inp_split(char *inst){

    int size = 64;
    char **out = malloc(size*sizeof(char *));
    char *delim = " ";
    next = 0;

    memerror(out);

    char *token = strtok(inst, delim);

    while(token != NULL){
        out[next] = token;
        next++;

        if(next>size){
            out = realloc(out, (size+64)*sizeof(char *));
            size = size+64;
            memerror(out);
        }

        token = strtok(NULL, delim);
    }

    out[next] = token;
    return out;

}


int execute(char **comms){

    if(inst[n-2]=='t' && inst[n-3]=='&'){
        char *sysarg;
        int i = 0;
        while(comms[i+1]!=NULL){
            strcat(sysarg,comms[i]);
            strcat(sysarg, " ");
            i++;
        }

        return thread_execute(sysarg);
    }

    if(comms[0]==NULL){
        return 1;
    }

    if(strcmp(comms[0],"cd")==0){
        return func_cd(comms);
    }
    else if(strcmp(comms[0],"pwd")==0){
        return func_pwd(comms);
    }
    else if(strcmp(comms[0],"echo")==0){
        return func_echo(comms);
    }
    else{
        return fork_execute(comms);
    }
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Fork execute & Thread execute

int fork_execute(char **args){
    if(strcmp(args[0],"ls")==0) return fork_ls(args);
    else if(strcmp(args[0],"cat")==0) return fork_cat(args);
    else if(strcmp(args[0],"date")==0) return fork_date(args);
    else if(strcmp(args[0],"rm")==0) return fork_rm(args);
    else if(strcmp(args[0],"mkdir")==0) return fork_mkdir(args);
    else return 0;
}


int thread_execute(char *args){

    pthread_t tid;

    pthread_create(&tid, NULL, &sys_call, args);

    pthread_join(tid, NULL);

    return 1;

}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////