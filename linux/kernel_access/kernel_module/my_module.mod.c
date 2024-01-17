#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/export-internal.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

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
	{ 0x88db9f48, "__check_object_size" },
	{ 0x7b10f2f7, "__nlmsg_put" },
	{ 0x82c87431, "param_ops_ulong" },
	{ 0x13c49cc2, "_copy_from_user" },
	{ 0xafd744c6, "__x86_indirect_thunk_rbp" },
	{ 0xb0e602eb, "memmove" },
	{ 0x9f3f8ed, "fget" },
	{ 0xfe202707, "register_ftrace_function" },
	{ 0x37a0cba, "kfree" },
	{ 0xddfe23c8, "__netlink_kernel_create" },
	{ 0x8b9200fd, "lookup_address" },
	{ 0xcbd4898c, "fortify_panic" },
	{ 0xbdfb6dbb, "__fentry__" },
	{ 0x65487097, "__x86_indirect_thunk_rax" },
	{ 0x92997ed8, "_printk" },
	{ 0xd0da656b, "__stack_chk_fail" },
	{ 0x8b73082f, "__alloc_skb" },
	{ 0xce543415, "ftrace_set_filter_ip" },
	{ 0x68f31cbd, "__list_add_valid" },
	{ 0xea378e6, "fput" },
	{ 0xed2d354b, "init_net" },
	{ 0xf33c2f36, "unregister_ftrace_function" },
	{ 0x262c9f92, "netlink_unicast" },
	{ 0x9166fada, "strncpy" },
	{ 0x25b29da6, "netlink_kernel_release" },
	{ 0xe1537255, "__list_del_entry_valid" },
	{ 0x98794516, "current_task" },
	{ 0xfb578fc5, "memset" },
	{ 0x5b8239ca, "__x86_return_thunk" },
	{ 0x6b10bee1, "_copy_to_user" },
	{ 0xfcca5424, "register_kprobe" },
	{ 0x63026490, "unregister_kprobe" },
	{ 0xeaa1fdc0, "kmalloc_trace" },
	{ 0x754d539c, "strlen" },
	{ 0xeb233a45, "__kmalloc" },
	{ 0x4ca346e5, "kmalloc_caches" },
	{ 0x6a2f2666, "d_path" },
	{ 0xb83992f2, "module_layout" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "8FD80BC5ED19DE75BB71098");
