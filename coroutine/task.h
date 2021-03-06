/*
 * @Author: Hobson
 * @Date: 2021-03-18 22:44:46
 * @Description:  协程对外接口
 * @LastEditTime: 2021-03-18 22:48:03
 */

#ifndef TASK_H_
#define TASK_H_

#include <stdint.h>

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
    struct context reg;
};

typedef struct task  *task_t;

extern int context_save(struct context *);
extern void context_recover(struct context *);

void yeild(void);
void resume(task_t task);

task_t task_creat(void (*func)(void *), uint32_t stack_size);

#endif
