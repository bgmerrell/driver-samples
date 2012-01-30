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
	{ 0x760f35f1, "cdev_alloc" },
	{ 0xa47b47fc, "module_refcount" },
	{ 0x52e1ba21, "cdev_del" },
	{ 0x6ed5c961, "cdev_init" },
	{ 0xd8e484f0, "register_chrdev_region" },
	{ 0x105e2727, "__tracepoint_kmalloc" },
	{ 0x7485e15e, "unregister_chrdev_region" },
	{ 0xea147363, "printk" },
	{ 0xbe499d81, "copy_to_user" },
	{ 0xb4390f9a, "mcount" },
	{ 0x7432f326, "cdev_add" },
	{ 0x93fca811, "__get_free_pages" },
	{ 0x37a0cba, "kfree" },
	{ 0x945bc6a7, "copy_from_user" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "13A581CECB526E5632D7486");
