/* **************** LF331:1.5 s_12/lab0_chrdrv.c **************** */
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
 *  lab0_chrdrv.c --- skeletal character driver illustrating only the
 *    basics of 'ioctl' operation.
 */
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <asm/ioctl.h>

#include "lab0_ioctl.h"  /* interface shared with user programs */

#define MYDEV_NAME "mycdrv"
#define ME MYDEV_NAME ": "     /* for use in printk() */

static dev_t first;
static unsigned int count = 1;
static struct cdev *my_cdev;

static struct class *my_sysfs_class;

/*
 *  ioctl() --- verify the user program's "cmd" and, when configuring the
 *   pretend device, the control register value the user says he wants to
 *   use.
 */
static long my_ioctl(struct file *file, unsigned int cmd, unsigned long data)
{
        struct my_ioctl_data my_data;
        long csr;  /* copy of my_data csr value */

        switch (cmd) {
        case MY_CMD_CONFIG:
                printk(KERN_INFO ME "CONFIG command\n");
                if (copy_from_user(&my_data, (void *) data,
                                   sizeof(struct my_ioctl_data))) {
                        printk(KERN_INFO ME "fault on copy_from_user\n");
                        return -EFAULT;
                }
                /* verify control register value, and pretend to set device */
                csr = my_data.csr.control_reg_value;
                if (csr != MY_CTRL_VAMPIRE &&
                    csr != MY_CTRL_UMPIRE  &&
                    csr != MY_CTRL_PERSPIRE) {
                        printk(KERN_INFO ME "invalid csr %lx\n", csr);
                        return -EINVAL;
                }
                /* pretend to put csr value into device here .... */
                printk(KERN_INFO ME "ioctl message %s\n",
                       my_data.message);
                
                /* mark message as empty, and put back a "status" reg val */
                my_data.message[0] = 0;

                /* for simple demo, just invert all the bits */
                my_data.csr.status_reg_value = ~csr;
                
                if (copy_to_user((void *) data, &my_data,
                                 sizeof(struct my_ioctl_data))) {
                        printk(KERN_INFO ME "fault on copy_to_user\n");
                        return -EFAULT;
                }
                printk(KERN_INFO ME "device configured\n");
                return 0;  /* success */

        case MY_CMD_START:
                printk(KERN_INFO ME "device started\n");
                return 0;

        case MY_CMD_STOP:
                printk(KERN_INFO ME "device stopped\n");
                return 0;

        default:
                printk(KERN_INFO ME "invalid cmd %x\n", cmd);
                return -EINVAL;
        }
}                        
                        
static const struct file_operations mycdrv_fops = {
        .owner = THIS_MODULE,
        .unlocked_ioctl = my_ioctl,
};

static int __init my_init(void)
{
        if (alloc_chrdev_region(&first, 0, count, MYDEV_NAME) < 0) {
                printk(KERN_ERR ME 
                       "failed to allocate character device region\n");
                return -1;
        }
        if (!(my_cdev = cdev_alloc())) {
                printk(KERN_ERR ME "cdev_alloc() failed\n");
                unregister_chrdev_region(first, count);
                return -1;
        }
        cdev_init(my_cdev, &mycdrv_fops);
        if (cdev_add(my_cdev, first, count) < 0) {
                printk(KERN_ERR ME "cdev_add() failed\n");
                cdev_del(my_cdev);
                unregister_chrdev_region(first, count);
                return -1;
        }
        my_sysfs_class = class_create(THIS_MODULE, "my_class");
        device_create(my_sysfs_class, NULL, first, NULL, "%s", "mycdrv");

        printk(KERN_INFO ME "simple ioctl chrdrv created, major %d\n",
               MAJOR(first));
        printk(KERN_INFO ME "sizeof(uint32_t) is %d\n", sizeof(uint32_t));
        return 0;
}

static void __exit my_exit(void)
{
        device_destroy(my_sysfs_class, first);
        class_destroy(my_sysfs_class);

        if (my_cdev)
                cdev_del(my_cdev);
        unregister_chrdev_region(first, count);
        printk(KERN_INFO ME "chrdrv unregistered\n");
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("Bill Kerr");
MODULE_DESCRIPTION("LF331:1.5 s_12/lab0_chrdrv.c");
MODULE_LICENSE("GPL v2");
