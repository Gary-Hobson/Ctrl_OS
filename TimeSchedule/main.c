#include "TimeSchedule.h"
#include <stdio.h>
#include <stdlib.h>

void func(void *arg)
{
    printf("Tick :%d, %s\n", millis(),arg);

    /*任务执行时间大于执行最小间隔，*/
    //usleep(1100*1000);
}

void stop_motor(void *arg);

void run_motor(void * arg)
{
    time_task_t task;

    printf("Tick :%d, 运行电机\n", millis());
    task = time_task_register(3000, stop_motor,NULL, TIME_SINGLE_TRIG);
    time_task_start(task, 0);
}

void stop_motor(void *arg)
{
    printf("Tick :%d, 停止电机\n", millis());
}


void setup(void)
{
    time_task_t task;

    task = time_task_register(1000, func, "检查按键状态", TIME_PERIODIC_TRIG);
    time_task_start(task, 0);
    task = time_task_register(2000, func, "读取传感器数据", TIME_PERIODIC_TRIG);
    time_task_start(task, 0);
    task = time_task_register(10000, run_motor, NULL, TIME_PERIODIC_TRIG);
    time_task_start(task, 0);
}

int main(int argc, char * argv[])
{
    setup();
    while (1)
    {
        time_task_schedule();
    }

}
