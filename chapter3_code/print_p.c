#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/list.h>

static int __init lkp_init( void ){
	struct task_struct *task, *p;
	struct list_head *pos;
	task = &init_task;
	list_for_each(pos, &task->tasks){
		p = list_entry(pos, struct task_struct, tasks);
		printk("%d: %s %d\n", p->pid, p->comm,p->state);
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
