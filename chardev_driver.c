

#include "chardev_driver.h"


static char device_buffer[BUFFER_SIZE];
static struct class *custom_pwm_class; // Global variable for the device class
static struct cdev pwm_cdev; // Global variable for the character device structure
static dev_t dev_num; // Global variable for the first device number
static struct file_operations PWM_driver_fops = 
{
    .owner   = THIS_MODULE,
    .read    = PWM_read,
    .write   = PWM_write,
};


// buffer we receive from user space.
// count is the size of the requested transfer (the size of the user buffer).
// *pos indicates the start position from which data should be read in the file
static ssize_t PWM_read(struct file *filp, char *buffer, size_t length, loff_t *offset){

    int maxbytes;           /* maximum bytes that can be read from ppos to BUFFER_SIZE*/
    int bytes_to_read;      /* gives the number of bytes to read*/
    int bytes_read;         /* number of bytes actually read*/
    maxbytes = BUFFER_SIZE - *offset;
    
    if (maxbytes > length)
        bytes_to_read = length;
    else
        bytes_to_read = maxbytes;
    if (bytes_to_read == 0)
        printk(KERN_INFO "charDev : Reached the end of the device\n");

    bytes_read = bytes_to_read - copy_to_user(buffer, device_buffer + *offset, bytes_to_read);
    printk(KERN_INFO "charDev : device has been read %d\n", bytes_read);

    *offset += bytes_read;
    printk(KERN_INFO "charDev : device has been read\n");

    return bytes_read;
}

// buffer coming from the user space.
// count is the size of the requested transfer.
// *pos indicates the start position from which data should be written in the file
static ssize_t PWM_write(struct file *filp, const char *buffer, size_t length, loff_t *offset){

    int maxbytes;           /* maximum bytes that can be read from ppos to BUFFER_SIZE*/
    int bytes_to_write;     /* gives the number of bytes to write*/
    int bytes_writen;       /* number of bytes actually writen*/
    maxbytes = BUFFER_SIZE - *offset;
    
    if (maxbytes > length)
        bytes_to_write = length;
    else
        bytes_to_write = maxbytes;

    bytes_writen = bytes_to_write - copy_from_user(device_buffer + *offset, buffer, bytes_to_write);
    printk(KERN_INFO "charDev : device has been written %d\n", bytes_writen);
    
    *offset += bytes_writen;
    printk(KERN_INFO "charDev : device has been written\n");
    
    return bytes_writen;
}

static int __init PMW_driver_init(void){
    
    init_PWM(PWM0);
    // raed_reg(12, 23);
    // int a = readl(12 + 23);
    /* Request for a major and PWM_DEV_NUM minors */
    if ( alloc_chrdev_region(&dev_num, 0, PWM_DEV_NUM, DEVICE_NAME) < 0 ) 
        goto chardev_region_failed;

    if (( custom_pwm_class = class_create(THIS_MODULE, CLASS_NAME)) == NULL)
        goto class_failed;


    if (device_create(custom_pwm_class, NULL, dev_num, NULL, DEVICE_NAME) == NULL)
        goto device_failed;


    cdev_init(&pwm_cdev, &PWM_driver_fops);
    if (cdev_add(&pwm_cdev, dev_num, PWM_DEV_NUM) == -1)
        goto cdev_failed;


    pr_info("PWM driver module was loaded\n" );
    return 0; 

cdev_failed:
    device_destroy(custom_pwm_class, dev_num);
device_failed:
    class_destroy(custom_pwm_class);
class_failed:
    unregister_chrdev_region(dev_num, PWM_DEV_NUM);
chardev_region_failed:
    return -1;       
}

static void __exit PMW_driver_exit(void){

    cdev_del(&pwm_cdev);
    device_destroy(custom_pwm_class, dev_num );
    class_destroy(custom_pwm_class);
    unregister_chrdev_region(dev_num, PWM_DEV_NUM);
    
    pr_info("PWM driver module was unloaded\n" );

}


module_init(PMW_driver_init);
module_exit(PMW_driver_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Custom module maden by Leo for PWM");
MODULE_AUTHOR("Leo");