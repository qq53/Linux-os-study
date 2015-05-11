#include<linux/module.h>
#include<linux/init.h>
#include<linux/interrupt.h>
#include<linux/sched.h>
#include<linux/string.h>
#include<linux/mm.h>

static int pid;

module_param(pid,int,0644);

static int __init memtest_init(void)
{
	struct task_struct *p;
	struct vm_area_struct *temp;
	unsigned long map_base;
	char flags[5];

	printk("The virtual memory areas(VMA) are:\n");
	p = pid_task(find_vpid(pid), PIDTYPE_PID);
	temp = p->mm->mmap;
	
	map_base = p->mm->mmap_base;
	while(temp)
	{
		strcpy(flags,"----");
		if(temp->vm_flags & VM_READ)
			flags[0] = 'r';
		if(temp->vm_flags & VM_WRITE)
			flags[1] = 'w';
		if(temp->vm_flags & VM_EXEC)
			flags[2] = 'x';
		if(temp->vm_flags & VM_SHARED)
			flags[3] = 'p';
		printk("start:%p\tend:%p\toffset:%lx\tflags:%s\n",(unsigned long *)temp->vm_start,(unsigned long *)temp->vm_end,temp->vm_start-map_base,flags);
		temp = temp->vm_next;
	}
	return 0;
}

static void __exit memtest_exit(void)
{
	printk("Unloading my module.\n");
	return;
}

module_init(memtest_init);
module_exit(memtest_exit);
MODULE_LICENSE("GPL");
