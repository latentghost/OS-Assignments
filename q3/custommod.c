#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/pid.h>
#include <linux/fs.h>
#include <linux/moduleparam.h>


pid_t pid1 = 0;

module_param(pid1,int,S_IRUSR);


MODULE_LICENSE("GPL");
MODULE_AUTHOR("latentghost");
MODULE_DESCRIPTION("takes pid of process as input and prints the pid, pid_g, usrgrp");


static int __init readprocess_init(void){
    struct task_struct *ts;
    struct pid *ps;
    printk(KERN_INFO "pid: %d" ,pid1);

    ps = find_get_pid(pid1);
    ts = pid_task(ps,PIDTYPE_PID);

    pid_t tg = ts->tgid;
    pid_t uid = ts->pid;
    printk(KERN_INFO "user id: %d" ,uid);
    printk(KERN_INFO "group id: %d" ,tg);
    return 0;
}

static void __exit readprocess_exit(void){
    printk(KERN_INFO "exiting module...\n");
    return;
}

module_init(readprocess_init);
module_exit(readprocess_exit);
