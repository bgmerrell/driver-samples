/* **************** LF331:1.6 s_18/lab8_uio_api_test.c **************** */
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
 * The UIO API (test program)
 *
@*/
#include  <stdlib.h>
#include  <stdio.h>
#include  <unistd.h>
#include  <fcntl.h>

int main()
{
	int fd;
	unsigned long nint;
	if ((fd = open("/dev/uio0", O_RDONLY)) < 0) {
		perror("Failed to open /dev/uio0\n");
		exit(EXIT_FAILURE);
	}
	fprintf(stderr, "Started uio test driver.\n");
	while (read(fd, &nint, sizeof(nint)) >= 0)
		fprintf(stderr, "Interrupts: %ld\n", nint);
	exit(EXIT_SUCCESS);
}
