#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/wait.h>
#include <asm/io.h>
#include "cdata_ioctl.h"
#include <linux/slab.h> 

#ifdef CONFIG_SMP
#define __SMP__
#endif

#define	CDATA_MAJOR 121 

struct cdata_t {
	char	data[1024];
}

static int cdata_open(struct inode *inode, struct file *filp)
{
	printk(KERN_ALERT "cdata: in cdata_open()\n");

	struct cdata_t *cdata;

	cdata =  (struct cdata_t*)kmalloc(sizeof(struct cdata_t), GFP_KERNEL);
	filp->private_data = (void *)data;
	return 0;
}

static int cdata_ioctl(struct inode *inode, struct file *filp, 
			unsigned int cmd, unsigned long arg)
{
	printk(KERN_ALERT "cdata: in cdata_ioctl()\n");
	switch(cmd)
	{
	  int i;
	  case IOCTL_EMPTY:
	  printk(KERN_ALERT "in ioctl:IOCTL_EMPTY\n");
	  for(i = 0; i< 1024; i++)	
	  	data[0] = "0"; 	
	  return 0;
	  case IOCTL_SYNC:
	  printk(KERN_ALERT "in ioctl:IOCTL_SYNC\n");
	  for(i = 0; i< 1024; i++)	
	  {	
		printk(KERN_ALERT "The data[%d] = (%s)\n",i, data[i]);
	  }
	  return 0;
	  default:
          return -ENOTTY; 		
	}
}

static ssize_t cdata_read(struct file *filp, char *buf, 
				size_t size, loff_t *off)
{
	printk(KERN_ALERT "cdata: in cdata_read()\n");
}

static ssize_t cdata_write(struct file *filp, const char *buf, 
				size_t size, loff_t *off)
{
	printk(KERN_ALERT "cdata_write: %s\n", buf);
	int i;

	for(i = 0; i< size; i++)	
	  	data[i] = buf[i];
	return 0;
}

static int cdata_release(struct inode *inode, struct file *filp)
{
	printk(KERN_ALERT "cdata: in cdata_release()\n");
	return 0;
}

struct file_operations cdata_fops = {	
	open:		cdata_open,
	release:	cdata_release,
	ioctl:		cdata_ioctl,
	read:		cdata_read,
	write:		cdata_write,
};

int my_init_module(void)
{
	register_chrdev(CDATA_MAJOR, "cdata", &cdata_fops);
	printk(KERN_ALERT "cdata module: registered.\n");

	return 0;
}

void my_cleanup_module(void)
{
	unregister_chrdev(CDATA_MAJOR, "cdata");
	printk(KERN_ALERT "cdata module: unregisterd.\n");
}

module_init(my_init_module);
module_exit(my_cleanup_module);

MODULE_LICENSE("GPL");
