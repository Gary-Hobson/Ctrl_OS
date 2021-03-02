/*
 * @Author: Hobson
 * @Date: 2021-02-28 19:24:12
 * @LastEditTime: 2021-03-02 23:30:13
 * @Description:  基于时间片的简单任务调度器
 * @Version: V0.0.1
 */

#include "PollSchedule.h"
#include "list.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
struct poll_task
{
    char *name;
    void *para;                 //任务参数
    int  (*detect)(void *data); //检查函数
    void (*func)(void * arg);   //任务函数
    void * user_data;
    enum TIME_MODE flag;        //执行模式
    struct list_head poll_node; //链表节点
};

/*初始化任务链表*/
LIST_HEAD(poll_list);

/*删除任务节点*/
static inline int poll_task_del(poll_task_t task)
{
    poll_task_t task_temp;

    /*查找待删除的任务*/
    list_for_each_entry(task_temp, &poll_list, poll_node)
    {
        if (task_temp == task)
        {
            list_del(&task_temp->poll_node);
            free(task);
            return 0;
        }
    }

    /*未找到任务节点*/
    return -1;
}

/*注册轮询任务，创建结构体进行赋值*/
poll_task_t poll_task_register(int (*detect_func)(void *data), void (*func)(void *arg), void *para)
{
    assert(func);
    assert(detect_func);

    poll_task_t task = malloc(sizeof(struct poll_task));
    task->detect = detect_func;
    task->func = func;
    task->para = para;

    list_add_tail(&task->poll_node, &poll_list);
    return task;
}

/*任务调度*/
void poll_task_schedule(void)
{
    poll_task_t task;

    /*循环判断是否满足任务执行条件*/
    list_for_each_entry(task, &poll_list, poll_node)
    {
        if (task->detect(task->para) == 1)
        {
            task->func(task->para);
        }
    }

    return;
}

void print_list(void)
{
    poll_task_t task;
    list_for_each_entry(task, &poll_list, poll_node)
    {
        printf("arg:%#x | ",task->para);
    }
    printf("\n\n");
}

