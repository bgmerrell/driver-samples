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
	{ 0x105e2727, "__tracepoint_kmalloc" },
	{ 0x28495076, "misc_register" },
	{ 0xea147363, "printk" },
	{ 0xbe499d81, "copy_to_user" },
	{ 0xb4390f9a, "mcount" },
	{ 0xfda85a7d, "request_threaded_irq" },
	{ 0xe523ad75, "synchronize_irq" },
	{ 0x93fca811, "__get_free_pages" },
	{ 0x37a0cba, "kfree" },
	{ 0xd9e36e6, "misc_deregister" },
	{ 0xf20dabd8, "free_irq" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "3B4FFDCA59EE99E96E4F6CB");
