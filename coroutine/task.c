/*
 * @Author: Hobson
 * @Date: 2021-03-18 21:31:49
 * @Description: 协程切换处理
 * @LastEditTime: 2021-03-18 22:47:47
 */
#include "task.h"
#include <stdint.h>
#include <stdlib.h>
#include "context.h"


struct task main_env, *curr_env;

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

task_t task_creat(void (*func)(void *), uint32_t stack_size)
{
    task_t task = (task_t)calloc(sizeof(struct task), 1);
    void *stack = (unsigned char *)malloc(stack_size);

    task->reg.rip = func;
    task->reg.rsp = stack + stack_size - 1;
    task->reg.rbp = stack + stack_size - 1;
    curr_env = task;

    return task;
}
