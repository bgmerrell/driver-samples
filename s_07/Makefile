### Automatic Makefile generation by 'genmake' script        ####
### Copyright, Jerry Cooperstein, coop@linuxfoundation.org 2/2003 - 1/2011 ####
### License: GPLv2 ###

obj-m +=  lab1_interrupt.o lab2_interrupt.o

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
	 lab2_getinterrupts

clean: kernel_clean
	rm -rf  lab2_getinterrupts  Module.symvers modules.order
