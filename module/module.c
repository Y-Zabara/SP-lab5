#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/ioctl.h>

#define DEVICE_NAME "virtualdevice"
#define IOCTL_RESET_COUNT _IO('k', 0)
#define IOCTL_INC_1 _IO('k', 1)
#define IOCTL_INC_2 _IO('k', 2)
#define IOCTL_INC_3 _IO('k', 3)
#define IOCTL_INC_4 _IO('k', 4)
#define IOCTL_INC_5 _IO('k', 5)
#define IOCTL_GET_COUNT _IOR('k', 6, int[5])

MODULE_LICENSE("GPL");

static int major;
static int cmd_counts[5];

static long device_ioctl(struct file *file, unsigned int ioctl_num, unsigned long ioctl_param) {
    switch (ioctl_num) {
        case IOCTL_RESET_COUNT:
            memset(cmd_counts, 0, sizeof(cmd_counts));
            break;
        case IOCTL_INC_1:
            cmd_counts[0]++;
            break;
        case IOCTL_INC_2:
            cmd_counts[1]++;
            break;
        case IOCTL_INC_3:
            cmd_counts[2]++;
            break;
        case IOCTL_INC_4:
            cmd_counts[3]++;
            break;
        case IOCTL_INC_5:
            cmd_counts[4]++;
            break;
        case IOCTL_GET_COUNT:
            if (copy_to_user((int __user *)ioctl_param, cmd_counts, sizeof(cmd_counts)))
                return -EFAULT;
            break;
        default:
            return -EINVAL;
    }
    return 0;
}

static struct file_operations fops = {
    .unlocked_ioctl = device_ioctl,
};

static int __init virtualdevice_init(void) {
    major = register_chrdev(0, DEVICE_NAME, &fops);
    if (major < 0) {
        printk(KERN_ALERT "Registering char device failed with %d\n", major);
        return major;
    }
    printk(KERN_INFO "Major number %d\n", major);
    printk(KERN_INFO "'mknod /dev/%s c %d 0'.\n", DEVICE_NAME, major);
    return 0;
}

static void __exit virtualdevice_exit(void) {
    unregister_chrdev(major, DEVICE_NAME);
    printk(KERN_INFO "Goodbye, world!\n");
}

module_init(virtualdevice_init);
module_exit(virtualdevice_exit);

