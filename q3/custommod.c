#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/moduleparam.h>


pid_t pid = 0;

module_param(pid,int,S_IRUSR);


MODULE_LICENSE("GPL");
MODULE_AUTHOR("latentghost");
MODULE_DESCRIPTION("takes pid of process as input and prints the pid, pid_g, usrgrp");


static int __init readprocess_init(void){
    struct task_struct *ts = (struct task_struct *) find_task_by_vpid(pid);
    printk(KERN_ALERT "pid: %d",pid);
    return 0;
}

static void __exit readprocess_exit(void){
    return;
}

module_init(readprocess_init);
module_exit(readprocess_exit);
