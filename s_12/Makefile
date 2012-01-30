### Automatic Makefile generation by 'genmake' script        ####
### Copyright, Jerry Cooperstein, coop@linuxfoundation.org 2/2003 - 1/2011 ####
### License: GPLv2 ###

obj-m +=  lab0_chrdrv.o lab1_ioctl_data.o lab2_ioctl_vardata.o lab3_ioctl_signal.o

export KROOT=/lib/modules/2.6.32-37-generic/build

allofit:  userprogs  modules
modules:
	@$(MAKE) -C $(KROOT) M=$(PWD) modules
modules_install:
	@$(MAKE) -C $(KROOT) M=$(PWD) modules_install
kernel_clean:
	@$(MAKE) -C $(KROOT) M=$(PWD) clean

userprogs:
	@$(MAKE) \
		CFLAGS="-O2 -Wall -pedantic" \
	 lab0_user_prog lab1_ioctl_data_test lab2_ioctl_vardata_test lab3_ioctl_signal_test

clean: kernel_clean
	rm -rf  lab0_user_prog lab1_ioctl_data_test lab2_ioctl_vardata_test lab3_ioctl_signal_test  Module.symvers modules.order
