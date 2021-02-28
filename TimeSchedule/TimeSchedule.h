/*
 * @Author: Hobson
 * @Date: 2021-02-28 19:17:43
 * @LastEditTime: 2021-02-28 19:46:31
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
typedef struct time_task * time_task_t;

extern uint32_t millis(void);

time_task_t time_task_register(uint32_t interval, void (*func)(void *arg), void *para, TIME_MODE flag);
void time_task_start(time_task_t task, uint32_t start_time);
int  time_task_delete(time_task_t task);
void time_task_schedule(void);

#ifdef __cplusplus 
}
#endif

#endif
