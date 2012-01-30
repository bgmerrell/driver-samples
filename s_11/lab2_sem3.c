/* **************** LF331:1.6 s_11/lab2_sem3.c **************** */
/*
 * The code herein is: Copyright the Linux Foundation, 2011
 *
 * This Copyright is retained for the purpose of protecting free
 * redistribution of source.
 *
 *     URL:    http://training.linuxfoundation.org
 *     email:  trainingquestions@linuxfoundation.org
 *
 * The primary maintainer for this code is Jerry Cooperstein
 * The CONTRIBUTORS file (distributed with this
 * file) lists those known to have contributed to the source.
 *
 * This code is distributed under Version 2 of the GNU General Public
 * License, which you should have received with the source.
 *
 */
/*
 * second and third module to test mutex contention.
 @*/

#include <linux/module.h>
#include <linux/init.h>
#include <asm/atomic.h>
#include <linux/errno.h>
#include <linux/version.h>
#include <linux/semaphore.h>

static char *modname = __stringify(KBUILD_BASENAME);

extern struct semaphore my_sem;

static int __init my_init(void)
{
	printk(KERN_INFO "Trying to load module %s\n", modname);
	printk(KERN_INFO "semaphore_count=%u\n", my_sem.count);

	if (down_trylock(&my_sem)) {
		printk(KERN_WARNING
		       "Not loading the module; down_trylock() failed\n");
		return -EBUSY;
	}
	printk(KERN_INFO "\nGrabbed semaphore in %s, ", modname);
	printk(KERN_INFO "semaphore_count=%u\n", my_sem.count);

	return 0;
}

static void __exit my_exit(void)
{
	up(&my_sem);
	printk(KERN_INFO "\nExiting semaphore in %s, ", modname);
	printk(KERN_INFO "semaphore_count=%u\n", my_sem.count);
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("Jerry Cooperstein");
MODULE_DESCRIPTION("LF331:1.6 s_11/lab2_sem3.c");
MODULE_LICENSE("GPL v2");
