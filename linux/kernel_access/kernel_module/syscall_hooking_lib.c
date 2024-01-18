//
// Created by idan on 1/16/24.
//

#include <linux/module.h>

#include "syscall_hooking_lib.h"

int set_addr_rw(unsigned long _addr) {

    unsigned int level;
    pte_t *pte = lookup_address(_addr, &level);

//    if (pte->pte & ~_PAGE_RW) {
    if (!(pte->pte & _PAGE_RW)) {
        pte->pte |= _PAGE_RW;
    }

    return 0;
}

int set_addr_ro(unsigned long _addr) {

    unsigned int level;
    pte_t *pte = lookup_address(_addr, &level);

    pte->pte = pte->pte & ~_PAGE_RW;

    return 0;
}

unsigned long get_syscall_func(uint16_t syscall_index, unsigned long *sys_call_table) {
    return sys_call_table[syscall_index];
}

void set_syscall_func(unsigned long func_addr, uint16_t syscall_index, unsigned long *sys_call_table) {
    sys_call_table[syscall_index] = func_addr;
}

void hook_syscall(struct syscall_hook_handle* handle, unsigned long *sys_call_table) {
    printk(KERN_INFO "hooking funciton");
    // store original syscall
    unsigned long orig = get_syscall_func(handle->syscall_index, sys_call_table);
    printk(KERN_INFO "stored original funciton: %p", orig);

    // set hook func
    printk(KERN_INFO "writing hook to table, in: %d, addr: %p", handle->syscall_index, handle->hook_func_addr);
    set_addr_rw(sys_call_table);
    set_syscall_func(handle->hook_func_addr, handle->syscall_index, sys_call_table);
    set_addr_ro(sys_call_table);

    printk(KERN_INFO "storing original in handle: %p", orig);
    handle->orig_syscall_addr = orig;
}

void unhook_syscall(struct syscall_hook_handle* handle, unsigned long *sys_call_table) {
    // set original syscall func
    set_addr_rw(sys_call_table);
    set_syscall_func(handle->orig_syscall_addr, handle->syscall_index, sys_call_table);
    set_addr_ro(sys_call_table);

    // reset hook handle
    handle->orig_syscall_addr = 0;
}