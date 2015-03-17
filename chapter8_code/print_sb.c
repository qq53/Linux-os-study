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
#include <linux/list.h>
#include <linux/spinlock.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>

static int __init lkp_init( void ){
	struct super_block *sb;
	struct list_head *pos;
	struct list_head *linode;
	struct inode *pinode;
	unsigned long long count = 0;

	printk("--print super_blocks--\n");
	spin_lock((spinlock_t*)0xc0e99ae0);
	list_for_each(pos, (struct list_head *)0xc0c9395c){
		sb = list_entry(pos, struct super_block, s_list);
		printk("dev_t: %d:%d\n",MAJOR(sb->s_dev), MINOR(sb->s_dev));
		printk("file_type: %s\n", sb->s_type->name);
	/*	list_for_each(linode, &sb->s_inodes){
			pinode = list_entry(linode, struct inode, i_sb_list);
			++count;
			printk("%lu\t", pinode->i_ino);
		}*/
	}
	spin_unlock((spinlock_t *)0xc0e99ae0);
	printk("number of inodes: %llu\n", count);
	return 0;
}

static void __exit lkp_cleanup( void ){
	printk("Goodbye World! from kernel space\n");
}

module_init(lkp_init);
module_exit(lkp_cleanup);
MODULE_LICENSE("GPL");
