#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sysrq.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Stanislaw Drozd");
MODULE_DESCRIPTION("Visual indication of SysRq uses");
MODULE_VERSION("0.1");

struct sysrq_key_op vsysrq_op = {
    .help_msg = "Blinks on successful entering raw mode",
    .action_msg = "Blink!",
};

void vsysrq_handler(int key);

static int vsysrq_init(void)
{
    vsysrq_op.handler = vsysrq_handler;

    printk(KERN_INFO "vsysrq: Starting!");

    if (register_sysrq_key('r', &vsysrq_op) == -1) {

        printk(KERN_ERR "vsysrq: Failed to register sysrq_key_op");
        return -1;
    }

    printk(KERN_INFO "Registered a sysrq_key_op");

    return 0;
}

static void vsysrq_exit(void)
{
    unregister_sysrq_key('r', &vsysrq_op);
    printk(KERN_INFO "vsysrq: Cleaning up!");
}

void vsysrq_handler(int key)
{
    printk(KERN_INFO "vsysrq handling the key like a champ!");
}

module_init(vsysrq_init);
module_exit(vsysrq_exit);
