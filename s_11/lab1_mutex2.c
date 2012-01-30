/* **************** LF331:1.6 s_11/lab1_mutex2.c **************** */
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
 * Semaphore Contention
 *
 * second and third module to test semaphores
 @*/

#include <linux/module.h>
#include <linux/init.h>
#include <linux/mutex.h>
#include <asm/atomic.h>
#include <linux/errno.h>

extern struct mutex my_mutex;

static char *modname = __stringify(KBUILD_BASENAME);

static int __init my_init(void)
{
	printk(KERN_INFO "Trying to load module %s\n", modname);
	printk(KERN_INFO "\n%s start count=%d:\n", modname,
	       atomic_read(&my_mutex.count));
#if 1
	if (mutex_lock_interruptible(&my_mutex)) {
		printk(KERN_INFO "mutex unlocked - wake up \n");
		return -1;
	}
#else
	mutex_lock(&my_mutex);
#endif
	printk(KERN_INFO "\n%s mutex put mutex, count=%d:\n",
	       modname, atomic_read(&my_mutex.count));

	return 0;
}

static void __exit my_exit(void)
{
	mutex_unlock(&my_mutex);
	printk(KERN_INFO "\n%s mutex end count=%d:\n",
	       modname, atomic_read(&my_mutex.count));
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("Tatsuo Kawasaki");
MODULE_DESCRIPTION("LF331:1.6 s_11/lab1_mutex2.c");
MODULE_LICENSE("GPL v2");
