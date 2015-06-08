/// \file consumer.c
/*
  ------------------------------------
  Create date : 2015-06-08 08:08
  Modified date: 2015-06-08 08:32
  Author : Sen1993
  Email : gsen1993@gmail.com
  ------------------------------------
*/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/semaphore.h>
#include <linux/sched.h>
#include <linux/atomic.h>
#include <linux/delay.h>
#include <linux/kthread.h>

#define PRODUCT_NUMS 10

static struct semaphore sem_producer;
static struct semaphore sem_consumer;
static char product[12];
static atomic_t num;
static int producer(void *product);
static int consumer(void *product);
static int id = 1;
static int consume_num = 1;

static int producer(void *p){
	char *product = p;
	int i;

	atomic_inc(&num);
	printk("producer [%d] start...\n", current->pid);
	for(i = 0; i < PRODUCT_NUMS; ++i){
		down(&sem_producer);
		snprintf(product, 12, "2010-01-%d", id++);
		printk("producer [%d] produce %s\n", current->pid, product);
		up(&sem_consumer);
	}
	printk("producer [%d] exit...\n", current->pid);
	return 0;
}

static int consumer(void *p){
	char *product = p;

	printk("consumer [%d] start...\n", current->pid);
	for(;;){
		msleep(100);
		down(&sem_consumer);
		if(consume_num >= PRODUCT_NUMS * atomic_read(&num))
			break;
		printk("consumer [%d] produce %s\n", current->pid, product);
		consume_num++;
		memset(product, 0, 12);
		up(&sem_producer);
	}
	printk("producer [%d] exit...\n", current->pid);
	return 0;
}

static int proc_init(void){
	printk(KERN_INFO"show producer and consumer\n");
	sema_init(&sem_producer, 1);
	sema_init(&sem_consumer, 0);
	atomic_set(&num, 0);
	kthread_run(producer, product, "mythread");
	kthread_run(consumer, product, "mythread");
	return 0;
}

static void proc_exit(void){
	printk(KERN_INFO"exit producer and consumer\n");
}

module_init(proc_init);
module_exit(proc_exit);
MODULE_LICENSE("GPL");
