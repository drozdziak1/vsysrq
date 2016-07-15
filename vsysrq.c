#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sysrq.h>
#include <linux/vt_kern.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Stanislaw Drozd");
MODULE_DESCRIPTION("Visual indication of Alt-SysRq-r");
MODULE_VERSION("0.1");

#define VSYSRQ_KEY 'y'

struct sysrq_key_op vsysrq_op;

void vsysrq_handler(int key);

static int vsysrq_init(void)
{
    int i;

    vsysrq_op.handler = vsysrq_handler;
    vsysrq_op.help_msg = "Blinks on successful entering raw mode";
    vsysrq_op.action_msg = "Blink!";
    vsysrq_op.enable_mask = 0x1;

    printk(KERN_INFO "vsysrq: Starting!\n");

    for (i = 0; i <=  3; ++i)
        printk(KERN_INFO "State of light %d is %d", i, vt_get_leds(0, i));


    if (register_sysrq_key(VSYSRQ_KEY, &vsysrq_op) == -1) {

        printk(KERN_ERR "vsysrq: Failed to register sysrq_key_op\n");
        return -1;
    }

    printk(KERN_INFO "Registered a sysrq_key_op\n");

    return 0;
}

static void vsysrq_exit(void)
{
    unregister_sysrq_key(VSYSRQ_KEY, &vsysrq_op);
    printk(KERN_INFO "vsysrq: Cleaning up!\n");
}

void vsysrq_handler(int key)
{
    printk(KERN_INFO "vsysrq handling the key like a champ!\n");
}

module_init(vsysrq_init);
module_exit(vsysrq_exit);
