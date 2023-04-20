ifneq ($(KERNELRELEASE),)

obj-m := chardev_driver.o
my_module-objs := PWM_controller.o

else

CROSS_COMPILE = /media/program/embeddedLinux/buildroot/output/host/bin/arm-linux-
KDIR = /media/program/embeddedLinux/buildroot/output/build/linux-custom/

default:
	clear
	$(MAKE) -C $(KDIR) M=$(PWD) ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE) modules
	make clean_trash
send:
	ssh rpi 'rm chardev_driver.ko'
	scp chardev_driver.ko rpi:/root

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) ARCH=arm64 CROSS_COMPILE=$(CROSS_COMPILE) clean

clean_trash:
	rm -rf *.o *~ core .depend .*.cmd *.mod.c *.mod *.symvers *.order .tmp_versions
endif