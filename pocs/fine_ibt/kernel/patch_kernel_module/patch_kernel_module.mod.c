#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/export-internal.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

#ifdef CONFIG_UNWINDER_ORC
#include <asm/orc_header.h>
ORC_HEADER;
#endif

BUILD_SALT;
BUILD_LTO_INFO;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
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
__used __section("__versions") = {
	{ 0x8a35b432, "sme_me_mask" },
	{ 0x88db9f48, "__check_object_size" },
	{ 0x650693a9, "_copy_from_user" },
	{ 0xb65f90cd, "proc_create" },
	{ 0xbe61bdb3, "pcpu_hot" },
	{ 0xcbd4898c, "fortify_panic" },
	{ 0xbdfb6dbb, "__fentry__" },
	{ 0x92997ed8, "_printk" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0xa916b694, "strnlen" },
	{ 0x4531ab62, "copy_from_kernel_nofault" },
	{ 0x7cd8d75e, "page_offset_base" },
	{ 0x1d19f77b, "physical_mask" },
	{ 0x2469810f, "__rcu_read_unlock" },
	{ 0x531b604e, "__virt_addr_valid" },
	{ 0xbcab6ee6, "sscanf" },
	{ 0x4a259e04, "proc_mkdir" },
	{ 0xfb578fc5, "memset" },
	{ 0x5b8239ca, "__x86_return_thunk" },
	{ 0x95954977, "proc_remove" },
	{ 0x90d8a54b, "pv_ops" },
	{ 0xe829452a, "module_layout" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "3B1FA58AC76024A42886890");
