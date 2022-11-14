#include <linux/kernel.h>
#include <linux/syscalls.h>


SYSCALL_DEFINE4(twodmemcpy, float**, src, float**, dest, int, csize, int, rsize)
{
	float buffer[4][4];

	for(int i=0; i<rsize; i++){
		if(__copy_from_user(&buffer[i], &src[i], sizeof(float) * (csize))){
			return -EFAULT;
		}
	}

	for(int i=0; i<rsize; i++){
		if(__copy_to_user(&dest[i], &buffer[i], sizeof(float) * (csize))){
			return -EFAULT;
		}
	}

//	for(int i=0; i<rsize; i++){
//		for(int j=0; j<csize; j++)
//			printf("%i ",dest[i][j]);
//		printf("\n");
//	}


	return 0;

}
