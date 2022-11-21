#include <linux/kernel.h>
#include <linux/syscalls.h>


SYSCALL_DEFINE4(twodmemcpy, float**, src, float**, dest, int, csize, int, rsize)
{
	float buffer[rsize][csize];

	if(__copy_from_user(buffer, src, sizeof(float) * (csize * rsize))){
		return -EFAULT;
	}

	if(__copy_to_user(dest, buffer, sizeof(float) * (csize * rsize))){
		return -EFAULT;
	}


	return 0;

}
