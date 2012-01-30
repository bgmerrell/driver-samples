#/* **************** LF331:1.6 s_05/lab4_loadit.sh **************** */
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
#!/bin/sh

# 1/2005 J. Cooperstein (coop@linuxfoundation.org) License:GPLv2

module=lab4_dynamic.ko
node=/dev/mycdrv
minor=0

[ "$1" != "" ] && module="$1"
[ "$2" != "" ] && node="$2"

echo loading $module
insmod $module

major=$(awk "\$2==\"mycdrv\" {print \$1}" /proc/devices)
echo major number is: $major

echo creating the device node at $node with minor number=0

mknod $node c $major $minor
