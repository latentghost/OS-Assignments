#include <stdio.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <linux/kernel.h>
#include <errno.h>

#define TWOD_MEMCPY 451


int main(int argc, char *argv[]){
	int c = 4, r = 3;
	float arr[3][4] = {{1.1,2.2,3.3,4.4},{9.1,8.2,7.3,6.4},{23.23,39.67,12.09,29.08}};
	float outarr[3][4];

	if(syscall(TWOD_MEMCPY, arr, outarr, c, r) != EFAULT){
		printf("twod_memcpy system call invoked\n");
		
		int b;
		for(int i=0; i<r; i++){
			b = 0;
			for(int j=0; j<c; j++){
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
