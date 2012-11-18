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
#include <asm/uaccess.h>

#ifdef CONFIG_SMP
#define __SMP__
#endif

#define	CDATA_MAJOR 121 
#define BUFSIZE 1024

struct cdata_t {
	char	data[BUFSIZE];
	int 	index;
};

static int cdata_open(struct inode *inode, struct file *filp)
{
	printk(KERN_ALERT "cdata: in cdata_open()\n");

	struct cdata_t *cdata;

	cdata =  kmalloc(sizeof(struct cdata_t), GFP_KERNEL);
	cdata->index = 0;
	filp->private_data = (void *)cdata;
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

	  return 0;
	  case IOCTL_SYNC:
	  printk(KERN_ALERT "in ioctl:IOCTL_SYNC\n");

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
				size_t count, loff_t *off)
{
	printk(KERN_ALERT "cdata_write: %s\n", buf);
	int i;
	struct cdata_t *cdata = (struct cdata_t *)filp->private_data;

	for(i = 0; i < count; i++) {
	  if(cdata->index >= BUFSIZE)
		return -EFAULT;

  	  if(copy_from_user(&cdata->data[cdata->index++], &buf[i], 1)) //Write data from user space to kernel space.
		return -EFAULT;
	}
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
