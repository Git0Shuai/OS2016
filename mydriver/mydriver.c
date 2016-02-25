/* 
 * OS2016/mydriver/mydriver.c
 *
 * a char divice driver.
 *
 *References:
 *  <<android xi tong yuan dai ma qing jing fen xi>>
 *  blog.chinaunix.net/uid-20799298-id-99675.html
 *  blog.csdn.net/shanzhizi/article/details/8626474
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/configfs.h>
#include <linux/version.h>
#include <linux/fs.h>   //register_chrdev()  unregister_chrdev()
#include <linux/init.h>
#include <linux/types.h>
#include <linux/uaccess.h> //copy_from_user() copy_to_user()
#include <linux/device.h>
#include <asm/uaccess.h>
#include <linux/slab.h> //kmalloc() free()
static int mydriver_open(struct inode *inode, struct file *filp);
static int mydriver_release(struct inode *inode, struct file *filp);
static ssize_t mydriver_read(struct file *filp, char *buf, size_t count, loff_t *f_pos);
static ssize_t mydriver_write(struct file *filp, const char *buf, size_t count, loff_t *f_pos);

struct file_operations mydriver_fops = {
    .open = mydriver_open,
    .release = mydriver_release,
    .read = mydriver_read,
    .write = mydriver_write,
};

int mydriver_major;
char *buf;

static int mydriver_init(void){  //make sense when insmod
    mydriver_major = register_chrdev(0, "mydriver", &mydriver_fops);
    if(mydriver_major < 0){
        printk("get mydriver major number failed!");
        return -1;
    }
    buf = kmalloc(1, GFP_KERNEL);
    printk("install mydriver Succeed!");
    return 0;
}

void mydriver_exit(void){   //make sense when rmmod
    if(buf)
        kfree(buf);
    unregister_chrdev(mydriver_major, "mydriver");
    printk("remove mydriver Succeed!");
}

module_init(mydriver_init);
module_exit(mydriver_exit);

static int mydriver_open(struct inode *inode, struct file *filp){
    if(!buf){
        printk("kmalloc buffer failed!");
        return -1;
    }
    printk("kmalloc buffer succeed!");
    return 0;
}

static int mydriver_release(struct inode *inode, struct file *filp){
    return 0;
}

static ssize_t mydriver_read(struct file *filp, char *user_buf, size_t count, loff_t *f_pos){
    if(count > 1024 || count < 0)
        return -1;
    copy_to_user(user_buf, buf, count);
    return 0;
}

static ssize_t mydriver_write(
        struct file *filp,
        const char *user_buf,
        size_t count, loff_t *f_pos){
    if(count > 1024 || count < 0)
        return -1;
    copy_from_user(buf, user_buf, count);
    return 0;
}


