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
	{ 0x5a5e7ea3, "simple_read_from_buffer" },
	{ 0xfb388461, "debugfs_create_dir" },
	{ 0x533f438, "debugfs_create_file" },
	{ 0x3c2c5af5, "sprintf" },
	{ 0xc437e684, "debugfs_create_u32" },
	{ 0xea147363, "printk" },
	{ 0x42224298, "sscanf" },
	{ 0xb4390f9a, "mcount" },
	{ 0xb858b265, "debugfs_remove" },
	{ 0x945bc6a7, "copy_from_user" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "F5316327F5923357FC4E02D");
