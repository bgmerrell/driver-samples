#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = KBUILD_MODNAME,
 .init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
 .exit = cleanup_module,
#endif
 .arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x8e49f4de, "module_layout" },
	{ 0xa47b47fc, "module_refcount" },
	{ 0x8bf7d1b0, "per_cpu__current_task" },
	{ 0x8a763823, "send_sig" },
	{ 0x891e02b1, "find_vpid" },
	{ 0x105e2727, "__tracepoint_kmalloc" },
	{ 0x28495076, "misc_register" },
	{ 0xea147363, "printk" },
	{ 0xb4390f9a, "mcount" },
	{ 0x44e2a393, "pid_task" },
	{ 0x93fca811, "__get_free_pages" },
	{ 0x37a0cba, "kfree" },
	{ 0xd9e36e6, "misc_deregister" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "7AA45D8E9D4DD164C131631");
