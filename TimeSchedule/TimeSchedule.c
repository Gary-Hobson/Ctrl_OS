/*
 * @Author: Hobson
 * @Date: 2021-02-28 19:24:12
 * @LastEditTime: 2021-02-28 21:52:52
 * @Description:  基于时间片的简单任务调度器
 * @Version: V0.0.1
 */

#include "TimeSchedule.h"
#include "list.h"
#include <stdlib.h>
#include <assert.h>

struct time_task
{
    uint32_t last_time;     //上次执行时间
    uint32_t interval;      //执行间隔
    void *para;             //任务参数
    void (*func)(void * arg);   //任务函数
    enum TIME_MODE flag;        //执行模式
    struct list_head time_node; //链表节点
};

/*初始化任务链表*/
LIST_HEAD(time_list);

/*插入任务到链表，按执行时间先后排列，依次递增*/
static inline void time_node_insert(time_task_t task)
{
    time_task_t task_temp;
    uint32_t next_time = task->last_time + task->interval;

    /*查找插入位置*/
    list_for_each_entry(task_temp, &time_list, time_node)
    {
        uint32_t next_time_temp = task_temp->interval + task_temp->last_time;
        if (next_time < next_time_temp)
        {
            list_add_tail(&task->time_node, &task_temp->time_node);
            return;
        }
    }

    list_add_tail(&task->time_node, &time_list);
    return;
}

/*查找待执行的任务*/
static inline time_task_t time_node_find(uint32_t curr_time)
{
    time_task_t task_temp;
    uint32_t next_time_temp;

    /*获取链表头节点*/
    task_temp = list_first_entry(&time_list, struct time_task, time_node);
    next_time_temp = task_temp->interval + task_temp->last_time;

    /*判断头节点是否到达执行时间*/
    if (curr_time >= next_time_temp)
    {
        list_del(&task_temp->time_node);
        return task_temp;
    }

    return NULL;
}

/*删除任务节点*/
static inline int time_node_del(time_task_t task)
{
    time_task_t task_temp;

    /*查找待删除的任务*/
    list_for_each_entry(task_temp, &time_list, time_node)
    {
        if (task_temp == task)
        {
            list_del(&task_temp->time_node);
            return 0;
        }
    }

    /*未找到任务节点*/
    return -1;
}

/*注册任务，创建结构体进行赋值*/
time_task_t time_task_register(uint32_t interval, void (*func)(void *arg), void *para, TIME_MODE flag)
{
    assert(func);

    time_task_t task = malloc(sizeof(struct time_task));
    task->flag = flag;
    task->func = func;
    task->interval = interval;
    task->para = para;

    return task;
}

/*
  * 计算下一次执行时间，将任务加入到待执行任务列表
  * start_time 参数为任务第一次开始执行时间，即延迟多少ms后开始进行调度
*/
void time_task_start(time_task_t task, uint32_t start_time)
{
    task->last_time =  start_time + millis();

    time_node_insert(task);
}

/*任务调度*/
void time_task_schedule(void)
{
    time_task_t task;
    uint32_t current_time = millis();

    task = time_node_find(current_time); //查找待执行任务,将任务节点取出
    if (task == NULL)
    {
        return;
    }

    /*更新执行时间，将任务节点重新插入*/
    if(task->flag == TIME_PERIODIC_TRIG)
    {
        time_task_start(task,0);        
    }

    task->func(task->para);             //运行定时任务
    
    if(task->flag == TIME_SINGLE_TRIG)  //删除单次执行任务
    {
        free(task);
    }
    return;
}

/*删除任务*/
int time_task_delete(time_task_t task)
{
    assert(task);

    /*删除任务节点*/
    time_node_del(task);
    free(task);
}

