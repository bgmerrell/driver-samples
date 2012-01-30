#/* **************** LF331:1.6 s_14/nomake.sh **************** */
#/*
# * The code herein is: Copyright the Linux Foundation, 2011
# *
# * This Copyright is retained for the purpose of protecting free
# * redistribution of source.
# *
# *     URL:    http://training.linuxfoundation.org
# *     email:  trainingquestions@linuxfoundation.org
# *
# * The primary maintainer for this code is Jerry Cooperstein
# * The CONTRIBUTORS file (distributed with this
# * file) lists those known to have contributed to the source.
# *
# * This code is distributed under Version 2 of the GNU General Public
# * License, which you should have received with the source.
# *
# */
#!/bin/bash

PATH=../:$PATH
cat *.c > /lib/firmware/my_fwfile
genmake $KROOT
make
