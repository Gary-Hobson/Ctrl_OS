/*
 * @Author: Hobson
 * @Date: 2021-02-28 19:17:43
 * @LastEditTime: 2021-03-02 22:11:14
 * @Description:  基于时间片的简单任务调度器
 * @Version: V0.0.1
 */

#ifndef TIME_TASK_H_
#define TIME_TASK_H_

#include <stdint.h>

#ifdef __cplusplus 
extern "C" { 
#endif

typedef enum TIME_MODE
{
    TIME_SINGLE_TRIG = 0x00,   
    TIME_PERIODIC_TRIG = 0x01, 
} TIME_MODE;

struct time_task;
struct poll_task;
typedef struct time_task * time_task_t;
typedef struct poll_task * poll_task_t;

extern uint32_t millis(void);

void poll_task_schedule(void);
poll_task_t poll_task_register(int (*detect_func)(void *data), void (*func)(void *arg), void *para);
static inline int poll_task_del(poll_task_t task);

#ifdef __cplusplus 
}
#endif

#endif
