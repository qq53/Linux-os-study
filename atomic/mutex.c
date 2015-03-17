/// \file mutex.c
/*
  ------------------------------------
  Create date : 2015-03-09 14:37
  Modified date: 2015-03-17 15:53
  Author : Sen1993
  Email : gsen1993@gmail.com
  ------------------------------------
*/
#include <linux/init.h>
#include <linux/module.h>
#include <linux/semaphore.h>

static int __init lkp_init( void ){
	DEFINE_SEMAPHORE(m);

	down(&m);
	printk("hello kernel space\n");
	up(&m);

	return 0;
}

static void __exit lkp_cleanup( void ){
	printk("Goodbye World! from kernel space\n");
}

module_init(lkp_init);
module_exit(lkp_cleanup);
MODULE_LICENSE("GPL");
