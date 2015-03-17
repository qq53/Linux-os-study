/// \file list.c
/*
  ------------------------------------
  Create date : 2015-03-09 14:37
  Modified date: 2015-03-12 01:12
  Author : Sen1993
  Email : gsen1993@gmail.com
  ------------------------------------
*/
#include <linux/init.h>
#include <linux/module.h>
#include <linux/atomic.h>

static int __init lkp_init( void ){
	atomic_t v = ATOMIC_INIT(1);

	atomic_sub(1,&v);
	printk("%d\n", atomic_read(&v));

	return 0;
}

static void __exit lkp_cleanup( void ){
	printk("Goodbye World! from kernel space\n");
}

module_init(lkp_init);
module_exit(lkp_cleanup);
MODULE_LICENSE("GPL");
