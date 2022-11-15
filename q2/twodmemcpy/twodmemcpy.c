#include <linux/kernel.h>
#include <linux/syscalls.h>


SYSCALL_DEFINE4(twodmemcpy, float**, src, float**, dest, int, csize, int, rsize)
{
	float buffer[rsize][csize];

	if(__copy_from_user(src, buffer, sizeof(float) * (csize * rsize))){
		return -EFAULT;
	}

	if(__copy_to_user(dest, buffer, sizeof(float) * (csize * rsize))){
		return -EFAULT;
	}


//	for(int i=0; i<rsize; i++){
//		for(int j=0; j<csize; j++)
//			printf("%i ",dest[i][j]);
//		printf("\n");
//	}


	return 0;

}
