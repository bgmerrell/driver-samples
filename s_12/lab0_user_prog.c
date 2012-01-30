/* **************** LF331:1.5 s_12/lab0_user_prog.c **************** */
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
 *  simple user-mode program to use the lab0_ioctl interface
 */
#include <stdio.h>
#include <stdlib.h>     /* needed for exit(3) */
#include <sys/types.h>  /* this, and the next two, needed for open(2) */
#include <sys/stat.h>
#include <fcntl.h>
#include <asm/ioctl.h>  /* this needed for the ioctl "cmd" definitions */
#include <sys/ioctl.h>  /* this needed for ioctl(2) syscall */
#include <string.h>     /* needed for strerror(3) */
#include <errno.h>      /* needed for errno variable */
#include <unistd.h>     /* probably not needed -- UNIX standard header */

#include <stdint.h>      /* for uint32_t and friends */
#include "lab0_ioctl.h"  /* my_ioctl interface definitions */

char *dev = "/dev/mycdrv";   /* default */

struct my_ioctl_data my_data;

int main(int ac, char **av)
{
        int fd;

        if (ac > 1)
                dev = av[1];

        if ((fd = open(dev, O_RDWR)) < 0) {
                fprintf(stderr, "can't open %s:  %s\n", dev,
                        strerror(errno));
                exit(1);
        }
        
        /* set the device configuration */
        my_data.csr.control_reg_value = MY_CTRL_VAMPIRE;
        sprintf(my_data.message, "I vant your blood");
        if (ioctl(fd, MY_CMD_CONFIG, &my_data) < 0) {
                fprintf(stderr, "CONFIG ioctl failed:  %s\n",
                        strerror(errno));
                exit(1);
        }
        printf("after CONFIG, status register is 0x%x.  Bitwise AND with "
               "control:  0x%x\n",
               my_data.csr.status_reg_value,
               my_data.csr.status_reg_value & MY_CTRL_VAMPIRE);
        fflush(stdout);

        if (ioctl(fd, MY_CMD_START) < 0) {
                fprintf(stderr, "START ioctl failed:  %s\n",
                        strerror(errno));
                exit(1);
        }
        printf("successfully started the device\n");
        fflush(stdout);
                
        if (ioctl(fd, MY_CMD_STOP) < 0) {
                fprintf(stderr, "STOP ioctl failed:  %s\n",
                        strerror(errno));
                exit(1);
        }
        printf("successfully stopped the device\n");
        fflush(stdout);

        close(fd);
        printf("sizeof(uint32_t) is %d\n", sizeof(uint32_t));
        return 0;  /* success */
}


