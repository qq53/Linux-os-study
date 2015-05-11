/// \file print_sb.c
/*
  ------------------------------------
  Create date : 2015-03-09 14:37
  Modified date: 2015-03-17 17:06
  Author : Sen1993
  Email : gsen1993@gmail.com
  ------------------------------------
*/
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/list.h>

static int __init lkp_init( void ){
	struct task_struct *task, *p;
	struct list_head *pos;
	unsigned int count = 0;
	task = &init_task;
	list_for_each(pos, &task->tasks){
		p = list_entry(pos, struct task_struct, tasks);
		++count;
		printk("%d %s\n", p->pid, p->comm);
	}
	printk("The sum of process: %u\n", count);

	return 0;
}

static void __exit lkp_cleanup( void ){
	printk("Goodbye World! from kernel space\n");
}

module_init(lkp_init);
module_exit(lkp_cleanup);
MODULE_LICENSE("GPL");
