ifneq ($(KERNELRELEASE),)
# kbuild part of makefile
obj-m := module.o
else
KDIR ?= /lib/modules/`uname -r`/build
default:
	$(MAKE) -C $(KDIR) M=$$PWD
clean:
	$(MAKE) -C $(KDIR) M=$$PWD clean
endif
