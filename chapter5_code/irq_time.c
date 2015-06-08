#include<linux/module.h>
#include<linux/init.h>
#include<linux/interrupt.h>
#include<linux/kernel.h>

static int irq = 19;
static char *interface = "eno16777736";
static int count = 0;

module_param(irq,int,0644);
module_param(interface,charp,0644);

static irqreturn_t intr_handler(int irq, void *dev_id)
{
	static long interval = 0;
	if(count == 0)
		interval = jiffies;

	interval = jiffies - interval;
	printk("the interval between two interrupts is %ld\n", interval);
	interval = jiffies;
	++count;

	return IRQ_NONE;
}

static int __init md_init(void){
	if( request_irq(irq, &intr_handler, IRQF_SHARED, interface, &irq) ){
		printk(KERN_ERR "fails to register IRQ %d\n", irq);
		return -EIO;
	}
	printk("%s Request on IRQ %d succeeded\n", interface, irq);
	return 0;
}

static void __exit md_exit(void)
{
	printk("the %d interrupts happened on irq %d\n", count, irq);
	free_irq(irq, &irq);
	printk("Freeing IRQ %d\n", irq);
	return;
}

module_init(md_init);
module_exit(md_exit);
MODULE_LICENSE("GPL");
