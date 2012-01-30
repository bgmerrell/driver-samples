/* **************** LF331:1.6 s_10/lab4_periodic_timers_alt.c **************** */
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
 * Multiple Periodic Kernel Timers
 *
 * Write a module that launches two periodic kernel timer functions;
 * i.e., they should re-install themselves.
 *
 * One periodic sequence should be for less than 256 ticks (so it
 * falls in the tv1 vector), and the other should be for less than 16
 * K ticks (so it falls in the tv2 vector.)
 *
 * Each time the timer functions execute, print out the total elapsed
 * time since the module was loaded (in jiffies).
 *
 @*/

#include <linux/module.h>
#include <linux/timer.h>
#include <linux/init.h>
#include <linux/jiffies.h>
#include <linux/slab.h>

static struct my_data {
	unsigned long period;
	unsigned long start_time;	/* jiffies */
	struct timer_list timer;
	char struct_id;		/* 'A' or 'B' */
} *data_array;			/* will kmalloc() an array of these */

static void my_timer_func(unsigned long var)
{
	struct my_data *dat = (struct my_data *)var;

	printk(KERN_INFO
	       "%c: period = %ld  elapsed = %ld\n",
	       dat->struct_id, dat->period, jiffies - dat->start_time);
	dat->start_time = jiffies;

	mod_timer(&dat->timer, dat->period + jiffies);
}

static int __init my_init(void)
{
	int i, period_in_secs;
	struct my_data *d;

	data_array = kmalloc(2 * sizeof(struct my_data), GFP_KERNEL);

	for (d = data_array, i = 0; i < 2; i++, d++) {
		init_timer(&d->timer);

		period_in_secs = (i == 0) ? 1 : 10;
		d->period = period_in_secs * HZ;
		d->struct_id = 'A' + i;
		d->start_time = jiffies;
		d->timer.function = my_timer_func;
		d->timer.expires = jiffies + d->period;
		d->timer.data = (unsigned long)d;

		add_timer(&d->timer);
	}
	printk(KERN_INFO "Module loaded, two HRTimers started\n");
	return 0;
}

static void __exit my_exit(void)
{
	int i;
	struct my_data *d = data_array;
	for (i = 0; i < 2; i++, d++) {
		printk(KERN_INFO "deleted timer %c:  rc = %d\n",
		       d->struct_id, del_timer(&d->timer));
	}
	kfree(data_array);
	printk(KERN_INFO "Module unloaded\n");
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("Jerry Cooperstein");
MODULE_AUTHOR("Bill Kerr");
MODULE_DESCRIPTION("LF331:1.6 s_10/lab4_periodic_timers_alt.c");
MODULE_LICENSE("GPL v2");
