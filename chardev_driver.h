
#ifndef CHARDEV_DRIVER
#define CHARDEV_DRIVER

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/printk.h>

// #include <linux/io.h>
#include "PWM_controller.h"

#define PWM_DEV_NUM 1
#define DEVICE_NAME "Custom_PWM_driver"
#define CLASS_NAME  "Custom_PWM_class"

#define BUFFER_SIZE 128


static ssize_t PWM_read(struct file *filp, char *buffer, size_t length, loff_t *offset);
static ssize_t PWM_write(struct file *filp, const char *buffer, size_t length, loff_t *offset);
static int __init PMW_driver_init(void);
static void __exit PMW_driver_exit(void);


#endif