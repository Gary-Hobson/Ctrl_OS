/*
 * @Author: Hobson
 * @Date: 2021-03-23 23:39:03
 * @Description: 
 * @LastEditTime: 2021-03-29 13:26:54
 */

#ifndef MESSAGE_H_
#define MESSAGE_H_

#include "list.h"
#include <stdlib.h>
#include <stdint.h>

typedef struct _message
{
    void *message_id;
    int state;
    uint16_t flag;
    void *data;
    struct list_head message_node; 
    struct list_head task_list_head; //挂载在该信号下的任务链表
} *message_t;

int publish_message(void *id, void *data, uint16_t flag);
int subscribe_message(void *id, task_t task, uint16_t flag);

#endif

