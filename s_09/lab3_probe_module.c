/* **************** LF331:1.6 s_09/lab3_probe_module.c **************** */
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
 * Probing a module
 *
 * Take an earlier character driver module and write a new module that
 * uses kprobes and jprobes to instrumentation the character driver.
 *
 * Does the function you are probing need to be exported to be
 * accessible to the probe utiltities?
 *
 @*/

#include <linux/module.h>
#include <linux/kprobes.h>
#include <linux/kallsyms.h>

static int mycdrv_open_probe(struct inode *inode, struct file *file)
{
	printk(KERN_INFO "\n\n ****JPROBE**** in mycdrv_open_debug\n\n");
	jprobe_return();
	return 0;
}

static struct kprobe kp;

static int handler_pre(struct kprobe *p, struct pt_regs *regs)
{
	printk(KERN_INFO "pre_handler: p->addr=0x%p\n", p->addr);
	return 0;
}

static void handler_post(struct kprobe *p, struct pt_regs *regs,
			 unsigned long flags)
{
	printk(KERN_INFO "post_handler: p->addr=0x%p\n", p->addr);
}

static int handler_fault(struct kprobe *p, struct pt_regs *regs, int trapnr)
{
	printk(KERN_INFO "fault_handler:p->addr=0x%p\n", p->addr);
	return 0;
}

static struct jprobe jp = {
	.kp.symbol_name = "mycdrv_generic_open",
	.entry = (kprobe_opcode_t *) mycdrv_open_probe,
};

static int __init my_init(void)
{
	/* set the handler functions */

	kp.pre_handler = handler_pre;
	kp.post_handler = handler_post;
	kp.fault_handler = handler_fault;
	kp.symbol_name = "mycdrv_generic_open";

	if (register_kprobe(&kp)) {
		printk(KERN_INFO "Failed to register kprobe, quitting\n");
		return -1;
	}
	register_jprobe(&jp);
	printk(KERN_INFO "plant jprobe at %p, handler addr %p\n", jp.kp.addr,
	       jp.entry);
	return 0;
}

static void __exit my_exit(void)
{

	unregister_jprobe(&jp);
	unregister_kprobe(&kp);
	printk(KERN_INFO "k,jprobes unregistered\n");
}

module_init(my_init);
module_exit(my_exit);
MODULE_AUTHOR("Jerry Cooperstein");
MODULE_DESCRIPTION("LF331:1.6 s_09/lab3_probe_module.c");
MODULE_LICENSE("GPL v2");
