#include <stdio.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <linux/kernel.h>
#include <errno.h>

#define TWOD_MEMCPY 451


int main(int argc, char *argv[]){
	float arr[][4] = {{1.1,2.2,3.3,4.4},{1.2,2.3,3.4,4.5},{9.1,8.2,7.3,6.4},{23.23,39.67,12.09,29.08}};
	float outarr[4][4];

	if(syscall(TWOD_MEMCPY, arr, outarr, 4, 4) != EFAULT){
		printf("twod_memcpy system call invoked\n");
		for(int i=0; i<4; i++){
			for(int j=0; j<4; j++)
				printf("%f ",outarr[i][j]);
			printf("\n");
		}
		int b;
		for(int i=0; i<4; i++){
			b = 0;
			for(int j=0; j<4; j++){
				if(arr[i][j] != outarr[i][j]){
					b = 1;
					printf("%i %i\n",i,j);
					printf("Error: copying unsuccesful\n");
					break;
				}
			}
			if(b) break;
		}
		if(!b) printf("Copying successful\n");
	}

	else{
		printf("Could not invoke syscall twod_memcpy\n");
	}
}
