#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>


#define NAME "./ofif"
#define READSIZE 100*sizeof(char)
#define SENDSIZE 3*sizeof(char)
#define LEN 7
#define ARRSIZE 50*sizeof(char *)


int main(){

    int f, r, out;
    char *rd = (char *) malloc(READSIZE);

    char *tmp = rd;
    int max = 0;

    f = open(NAME, O_RDONLY);
    r = read(f, rd, 100);

    for(int j=0; j<5; j++){
        
        // print index
        int ind = (int) (*tmp);
        ind -= 48;
        tmp++;
        int j = (int) (*tmp);
        if(j>=48 && j<=57){
            ind *= 10;
            ind += j-48;
            tmp++;
        }

        printf("%i ", ind);

        // print the string
        for(int i=0; i<LEN; i++){
            printf("%c", *(tmp));
            tmp++;
        }

        // only store the last index
        if(ind>max) max = ind;
        printf("\n");
    }

    close(f);
    printf("\n");

    f = open(NAME, O_WRONLY);

    // return the highest index received to p1
    char outind[3];
    outind[2] = '\0';
    if(max<10){
        outind[0] = (char) (48 + max);
        outind[1] = '~';
    }
    else{
        outind[0] = (char) (48 + max/10);
        outind[1] = (char) (48 + max%10);
    }

    write(f, outind, sizeof(outind));
    close(f);

    return 0;

}