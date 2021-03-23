/*
 * @Author: Hobson
 * @Date: 2021-03-18 22:44:46
 * @Description:  协程对外接口
 * @LastEditTime: 2021-03-23 22:36:50
 */

#ifndef TASK_H_
#define TASK_H_

#include "list.h"
#include <stdint.h>
#include <stdbool.h>

struct context
{
    void *rsp;
    void *rbp;
    void *rip;
    void *r12;
    void *r13;
    void *r14;
    void *r15;
    void *rdi;
    void *rsi;
    void *rcx;
    void *rax;
    void *rbx;
};

struct task
{
    const char *name;
    struct context reg;
    int state;
    struct list_head task_node;
    char stack[];
};
enum
{
    TASK_INIT,
    TASK_RUN,
    TASK_SUSPEND,
    TASK_READY,
    TASK_DIED
};

typedef struct task  *task_t;

extern int context_save(struct context *);
extern void context_recover(struct context *);

void yeild(void);
void resume(task_t task);

task_t task_creat(void (*func)(void *), uint32_t stack_size);
void task_set_name(task_t task, const char *name);
void task_schedule(void);

#endif
