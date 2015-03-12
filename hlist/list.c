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
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/list.h>
#include <linux/slab.h>

struct myhlist{
	int n;
	struct hlist_node node;
};

static inline struct hlist_node *create_myhlist( int n ){
	struct myhlist *p = (struct myhlist *)kmalloc(sizeof(struct myhlist), GFP_KERNEL);
	INIT_HLIST_NODE(&p->node);
	p->n = n;
	return &p->node;
}

static int __init lkp_init( void ){
	HLIST_HEAD(hhead);
	struct myhlist *pp;

	hlist_add_head(create_myhlist(1), &hhead);

	hlist_for_each_entry(pp, &hhead, node){
		printk("%d ", pp->n);
	}
	printk("\n");

	struct hlist_node *pn;
	hlist_for_each_entry_safe(pp, pn, &hhead, node){
		if(pn)
			hlist_del(pn);
		kfree(pp);
	}
	return 0;
}

static void __exit lkp_cleanup( void ){
	printk("Goodbye World! from kernel space\n");
}

module_init(lkp_init);
module_exit(lkp_cleanup);
MODULE_LICENSE("GPL");
