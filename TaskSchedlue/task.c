/*
 * @Author: Hobson
 * @Date: 2021-03-18 21:31:49
 * @Description: 协程切换处理
 * @LastEditTime: 2021-03-23 23:06:55
 */

#include "list.h"
#include "task.h"
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

void (*task_switch_hook)(void) = NULL;
struct task main_env, *curr_env;

LIST_HEAD(task_list);

static void task_switch(struct context *from, struct context *to)
{
    int ret;
    ret = context_save(from);
    if (ret == 0)
    {
        context_recover(to);
    }
}

void yeild(void)
{
    task_switch(&curr_env->reg, &main_env.reg);
}

void resume(task_t task)
{
    curr_env = task;

    task_switch(&main_env.reg, &task->reg);
}

void task_set_name(task_t task, const char *name)
{
    task->name = name;
}

void tesk_exit();

task_t task_creat(void (*func)(void *), uint32_t stack_size)
{
    task_t task = malloc(sizeof(struct task) + stack_size);

    task->reg.rip = func;
    task->reg.rsp = task->stack + stack_size - 16;
    task->reg.rbp = task->stack + stack_size -16;
    *(void (**)(void))(task->stack + stack_size - sizeof(void *)) = (void (*)(void))tesk_exit;
    list_add(&task->task_node, &task_list);

    return task;
}

/*设置任务切换钩子*/
void task_set_switch_hook(void (*hook)())
{
    task_switch_hook = hook;
}

bool task_switch_manager(task_t task)
{

    if (task->state == TASK_DIED)
    {
        list_del(&task->task_node);
        return false;
    }
    return true;
}


void tesk_exit()
{
    printf("test :%s exit\n",curr_env->name);

    curr_env->state = TASK_DIED;
    context_recover(&main_env.reg);
}

void task_schedule(void)
{
    task_t task,temp;
    for (;;)
    {
        list_for_each_entry_safe(task, temp, &task_list, task_node)
        {

            /*任务切换策略单独处理*/
            if (task_switch_manager(task) == false)
            {
                continue;
            }

            if (task_switch_hook != NULL)
            {
                task_switch_hook();
            }

            resume(task);
        }
    }
}
