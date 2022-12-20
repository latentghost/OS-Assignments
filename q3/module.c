#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/moduleparam.h>


pid_t pid = 0;

module_param(pid,pid_t,S_IRUSR);

void printpid(){
    printk(KERN_INFO "PID: %d",pid);
}


MODULE_LICENSE("GPL");
MODULE_AUTHOR("latentghost");
MODULE_DESCRIPTION("takes pid of process as input and prints the ")


static int __init readprocess_init(void){
    printpid();
    return 0;
}

static void __exit readprocess_exit(void){
    return;
}