#include <linux/build-salt.h>
#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(.gnu.linkonce.this_module) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section(__versions) = {
	{ 0x8ed3c35e, "module_layout" },
	{ 0x5140db62, "wake_up_process" },
	{ 0x3448988a, "kthread_bind" },
	{ 0x28b3938b, "kthread_create_on_node" },
	{ 0x437edb9e, "kthread_stop" },
	{ 0x1000e51, "schedule" },
	{ 0x955a832f, "___preempt_schedule" },
	{ 0x4629334c, "__preempt_count" },
	{ 0x706c5a65, "preempt_count_sub" },
	{ 0x7a2af7b4, "cpu_number" },
	{ 0xc38259af, "__this_cpu_preempt_check" },
	{ 0xf229424a, "preempt_count_add" },
	{ 0xb3f7646e, "kthread_should_stop" },
	{ 0xc5850110, "printk" },
	{ 0xbdfb6dbb, "__fentry__" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "227BC464048D79B630303C8");
