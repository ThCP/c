/**
	This is the code needed to create a module able to read and write from input.
	
	I completed the code needed in some functions.
	
	Riccardo Cappuzzo
	
	sysprog04
	
*/

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <asm/uaccess.h> // copy_to_user and from_user

#define DEVICE_NAME 			"my_device"
#define MAJOR_DEVICE_NUMBER 	60
#define MINOR_DEVICE_NUMBER 	0
#define BUF_LEN 				1024

static char msg[BUF_LEN];
static char *msg_ptr; //
static int major;

/* new variables*/
static int device_open = 0; // used to prevent concurrent access into the same device
//static char * buf;
static char *msg_reading_offset;


MODULE_AUTHOR("Riccardo Cappuzzo");
MODULE_LICENSE("GPL");

/* PROTOTYPES */
static ssize_t my_read (
	struct file *filp, char __user *buf,
	size_t length, loff_t *offset);
static ssize_t my_write (
	struct file *filp, const char __user *buf,
	size_t length, loff_t *offset);
static int my_open (struct inode *inode,
	struct file *filp);
static int my_close (struct inode *inode,
	struct file *filp);
	
static int __init my_init (void);
static void __exit my_cleanup (void);
/* END PROTOTYPES */ 

static struct file_operations fops = {
	.read = my_read,
	.write = my_write,
	.open = my_open,
	.release = my_close,
};

// this is called when a process tries to open the device file
static int my_open (struct inode *inode,
	struct file *filp)
{
	if (device_open) // if device_open != 0, leave as the device is busy
		return -EBUSY;
	
	// the device is now busy
	device_open = 1;
	
	msg_reading_offset = msg;
	return 0;
}

//this is called when the process closes the device
static int my_close (struct inode *inode,
	struct file *filp)
{
	device_open = 0; // the device is now free
	return 0;
}

// this is called when the process tries to read from the device
static ssize_t my_read (
	struct file *filp, char __user *buf,
	size_t length, loff_t *offset)
{
	int nc = 0; 
	
	// if no more "valid" bytes can be read, stop (EOF reached)
	if (*msg_reading_offset == 0) return 0;

	// no negative values allowed
	if (length < 0)
		return -EINVAL;

	// if the number of characters in input is smaller than the length, fix the value of the length
	if (length > strlen(msg)) {
		length = strlen(msg);
	}
	
	// nc is the number of characters not correctly copied
	nc = copy_to_user(buf, msg_reading_offset, length);
	/*
		updates the current reading offset pointer so that a
		recursive call due to not original
		full length will get a 0 (nothing to read)
	*/
	msg_reading_offset += sizeof(char) * (length-nc);
	
	// returns the number of REAL bytes read.
	return length - nc;
}

// this is called when a process attempts to read from the device
static ssize_t my_write (
	struct file *filp, const char __user *buf,
	size_t length, loff_t *offset)
{
	int nc = 0;
	if (length > BUF_LEN)
		return BUF_LEN-length;
	nc = copy_from_user(msg, buf, length);
	msg_ptr = msg;
	return length - nc;
}

// this is called when I first add the module to the kernel
static int __init my_init (void)
{
	major = register_chrdev (MAJOR_DEVICE_NUMBER,
				DEVICE_NAME,
				&fops);
				
	// error check for the major: if the value is smaller than 0 then the registration failed
	if (major < 0) {
		printk (KERN_ALERT "Registering char device failed with major %d\n", major);
		return major;
	}
	
	printk (KERN_INFO "%s\nMajor device number: %d\n", "Registration successfull", MAJOR_DEVICE_NUMBER);
	
	// no errors occurred, proceed

	return major;
}
module_init(my_init);

static void __exit my_cleanup (void)
{
	unregister_chrdev (major, DEVICE_NAME); 
}
module_exit(my_cleanup);
