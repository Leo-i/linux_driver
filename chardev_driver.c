#include <linux/init.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/of.h>
#include <linux/fs.h>

#define PWM_DEV_NUM 1
#define DEVICE_NAME "Custom_PWM_driver"
#define CLASS_NAME  "Custom_PWM_class"

static ssize_t PWM_read(struct file *, char __user *, size_t, loff_t *pos);
static ssize_t PWM_write(struct file *, const char __user *, size_t, loff_t *pos);
static int __init my_init(void);
static void __exit PMW_driver_exit(void);

static struct class *custom_pwm_class;
static struct cdev pwm_cdev;
static dev_t dev_num;
static struct file_operations PWM_driver_fops = 
{
    .owner   = THIS_MODULE,
    .read    = PWM_read,
    .write   = PWM_write,
};


// *buf is the buffer we receive from user space.
// count is the size of the requested transfer (the size of the user buffer).
// *pos indicates the start position from which data should be read in the file
static ssize_t PWM_read(struct file *, char __user *, size_t, loff_t *pos){

    printk("PWM driver read function called" );
    return 4;
}

// *buf represents the data buffer coming from the user space.
// count is the size of the requested transfer.
// *pos indicates the start position from which data should be written in the file
static ssize_t PWM_write(struct file *, const char __user *, size_t, loff_t *pos){

    printk("PWM driver write function called" );
    return 5;
}

static int __init my_init(void){
    int i;
    dev_t curr_dev;
    /* Request for a major and PWM_DEV_NUM minors */
    alloc_chrdev_region(&dev_num, 0, PWM_DEV_NUM, DEVICE_NAME);

    /* create our device class, visible in /sys/class */
    custom_pwm_class = class_create(THIS_MODULE, CLASS_NAME);

    /* Each device is represented as a character device (cdev) */
    for (i = 0; i < PWM_DEV_NUM; i++) {

        /* bind file_operations to the cdev */
        cdev_init(&pwm_cdev[i], &PWM_driver_fops);
        pwm_cdev[i].owner = THIS_MODULE;

        /* Device number to use to add cdev to the core */
        curr_dev = MKDEV(MAJOR(dev_num),
        MINOR(dev_num) + i);

        /* Make the device live for the users to access */
        cdev_add(&pwm_cdev[i], curr_dev, 1);

        /* create a node for each device */
        device_create(custom_pwm_class,
                        152 Writing Character Device Drivers
                        NULL, /* no parent device */
                        curr_dev,
                        NULL, /* no additional data */
                        DEVICE_NAME "%d", i); /* eep-mem[0-7] */
    }
    
    printk("PWM driver module was loaded" );
    return 0;
}

static void __exit PMW_driver_exit(void){
    for (i = 0; i < PWM_DEV_NUM; i++) {
        device_destroy(custom_pwm_class, MKDEV(MAJOR(dev_num), (MINOR(dev_num) +i)));
        cdev_del(&pwm_cdev[i]);
    }
    class_unregister(custom_pwm_class);
    class_destroy(custom_pwm_class);
    unregister_chrdev_region(chardev_devt, PWM_DEV_NUM);

}


module_init(PMW_driver_init);
module_exit(PMW_driver_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Custom module maden by Leo for PWM");
MODULE_AUTHOR("Leo");


