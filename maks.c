#include <linux/kernel.h> 
#include <linux/module.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h> 
#include <linux/version.h> 
#include <linux/sched.h> 
#include <linux/sched/signal.h> 


#define maks_kernel_build
#include "maks.h"

#define ERROR 500

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5, 6, 0) 
#define HAVE_PROC_OPS 
#endif 

#define PROCFS_MAX_SIZE 1024 
#define PROCFS_NAME "maks_module" 

/* Эта структура содержит информацию о файле /proc. */ 
static struct proc_dir_entry * our_proc_file; 

/* Этот буфер используется под хранение символа для данного модуля. */ 
static char procfs_buffer[PROCFS_MAX_SIZE]; 
 
/* Размер буфера. */ 
static unsigned long procfs_buffer_size = 0; 
 
/* Эта функция вызывается при считывании пользователем из файла /proc. */ 
static ssize_t procfile_read(struct file * filePointer, char __user * buffer, 
                             size_t buffer_length, loff_t * offset) 
{ 
    int pid;
    sscanf(procfs_buffer, "%d", &pid);
    pr_info("PID was got: %d\n", pid);
    
    struct task_struct* task;
    task = get_pid_task(find_get_pid(pid), PIDTYPE_PID);
    if (task == NULL) {
        pr_err("Failed to read thread with PID %d\n", pid);
        return ERROR;
    }
    
    struct signal_struct * sig = task->signal;
    struct maks_transfer_struct m_transfer_struct;



    m_transfer_struct.sigcnt = sig->sigcnt.refs.counter;
    m_transfer_struct.nr_threads = sig->nr_threads;
    m_transfer_struct.group_exit_code = sig->group_exit_code;
    m_transfer_struct.notify_count = sig->notify_count;
    m_transfer_struct.group_stop_count = sig->group_stop_count;
    m_transfer_struct.flags = sig->flags;
    m_transfer_struct.leader = sig->leader;
    m_transfer_struct.utime = sig->utime;
    m_transfer_struct.stime = sig->stime;
    m_transfer_struct.cutime = sig->cutime;
    m_transfer_struct.cstime = sig->cstime;
    m_transfer_struct.gtime = sig->gtime;
    m_transfer_struct.cgtime = sig->cgtime;
    m_transfer_struct.sum_sched_runtime = sig->sum_sched_runtime;
    m_transfer_struct.task_cpu_time_utime = task->utime;
    m_transfer_struct.task_cpu_time_stime = task->stime;

    int len = sizeof(struct maks_transfer_struct); 
    ssize_t ret = len; 

    if (*offset >= len || copy_to_user(buffer, &m_transfer_struct, len)) { 
        pr_info("copy_to_user failed\n"); 
        ret = 0; 
    } else { 
        pr_info("procfile read %s\n", filePointer->f_path.dentry->d_name.name); 
        *offset += len; 
    }
    return ret; 
} 

 /* Эта функция вызывается при записи пользователем в файл /proc. */ 
static ssize_t procfile_write(struct file *file, const char __user *buff, 
                              size_t len, loff_t *off) 
{ 
    procfs_buffer_size = len; 
    if (procfs_buffer_size > PROCFS_MAX_SIZE) 
        procfs_buffer_size = PROCFS_MAX_SIZE; 
 
    if (copy_from_user(procfs_buffer, buff, procfs_buffer_size)) 
        return -EFAULT; 
 
    procfs_buffer[procfs_buffer_size & (PROCFS_MAX_SIZE - 1)] = '\0'; 
    pr_info("procfile write %s\n", procfs_buffer); 
 
    return procfs_buffer_size; 
} 

#ifdef HAVE_PROC_OPS 
static const struct proc_ops proc_file_fops = { 
    .proc_read = procfile_read, 
    .proc_write = procfile_write, 
}; 
#else 
static const struct file_operations proc_file_fops = { 
    .read = procfile_read, 
    .write = procfile_write, 
}; 
#endif 

static int __init maks_init( void ) {
 	pr_info( "Maks module init" );

    our_proc_file = proc_create(PROCFS_NAME, 0666, NULL, &proc_file_fops); 
    if (NULL == our_proc_file) { 
        proc_remove(our_proc_file); 
        pr_alert("Error:Could not initialize /proc/%s\n", PROCFS_NAME); 
        return -ENOMEM; 
    } 
 
    pr_info("/proc/%s created\n", PROCFS_NAME); 
 return 0;
}

static void __exit max_exit( void ) {
	proc_remove(our_proc_file); 
    pr_info( "Maks module exit" );
}

module_init( maks_init );
module_exit( max_exit ); 

MODULE_LICENSE( "GPL" );
MODULE_AUTHOR( "Maks" );
