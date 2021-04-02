/*
 * @Author: Hobson
 * @Date: 2021-03-24 00:15:32
 * @Description:
 * @LastEditTime: 2021-04-02 09:30:31
 */

#include "task.h"
#include "message.h"

LIST_HEAD(message_list);
LIST_HEAD(message_queue);

message_t create_message(void *id);

/*查找信息id对应的结构体*/
static message_t find_message(void *id)
{
    message_t message = NULL;
    list_for_each_entry(message, &message_list, message_node)
    {
        if(message->message_id == id)
        {
            return message;
        }
    }

    message = create_message(id);

    return message;
}

//插入消息到到消息队列
static void insert_message(message_t message)
{
    //从消息链表中取出，加入到新的消息队列链表
    list_splice_tail_init(&message->task_list_head, &task_list);
}

/*创建一个消息结构体，保存信息*/
message_t create_message(void *id)
{
    message_t message = malloc(sizeof(struct _message));
    assert(message);
    message->message_id = id;
    message->data = NULL;
    INIT_LIST_HEAD(&message->message_node);
    INIT_LIST_HEAD(&message->task_list_head);
    list_add(&message->message_node, &message_list);

    return message;
}

/*发布一个消息*/
int publish_message(void *id, void *data, uint16_t flag)
{
    message_t message = find_message(id);

    if (message == NULL)
    {
        message = create_message(id);
    }

    insert_message(message);
}

/*订阅一个消息*/
int subscribe_message(void *id, task_t task, uint16_t flag)
{
    message_t message = find_message(id);
    list_move(&task->task_node, &message->task_list_head);
}



