ifneq ($(KERNELRELEASE),)

obj-m += pwm_driver.o  ## built as loadable kernel modules
pwm_driver-objs += PWM_controller.o chardev_driver.o

else

CROSS_COMPILE = /media/program/embeddedLinux/buildroot/output/host/bin/arm-linux-
KDIR = /media/program/embeddedLinux/buildroot/output/build/linux-custom/
PWD  := $(shell pwd)

default:
	clear
	$(MAKE) -C $(KDIR) M=$(PWD) SUBDIRS=$(PWD) ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE) modules
	make clean_trash

send:
	ssh rpi 'rm chardev_driver.ko'
	scp chardev_driver.ko rpi:/root

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) ARCH=arm64 CROSS_COMPILE=$(CROSS_COMPILE) clean

clean_trash:
	find . ! -name '*.ko' ! -name '*.c' ! -name '*.h' ! -name 'Makefile' -type f -delete
endif