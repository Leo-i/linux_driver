ifneq ($(KERNELRELEASE),)

obj-m := chardev_driver.o

else

CROSS_COMPILE = /media/program/embeddedLinux/buildroot/output/host/bin/arm-linux-
KDIR = /media/program/embeddedLinux/buildroot/output/build/linux-custom/

default:
	clear
	$(MAKE) -C $(KDIR) M=$(PWD) ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE) modules
	
clean:
	$(MAKE) -C $(KDIR) M=$(PWD) ARCH=arm64 CROSS_COMPILE=$(CROSS_COMPILE) clean

endif