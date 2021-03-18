/*
 * @Author: Hobson
 * @Date: 2021-03-17 12:55:13
 * @Description: 使用协程实现生产者消费者
 * @LastEditTime: 2021-03-18 23:01:03
 */

#include "task.h"
#include <unistd.h>
#include <stdio.h>

/*库存产品数量*/
uint16_t product = 0;

/*定义两个任务句柄*/
task_t producer_task, consumer_task;

/*生产者*/
void producer(void *arg)
{
    while (1)
    {
        product += 2;   //生产产品
        printf("manefaceture product,  stock product: %d\n", product);
        sleep(1);       //模拟时间消耗
        
        /*切换到其他任务*/
        yeild();
    }
}

/*消费者*/
void consumer(void *arg)
{
    int cnt = 0;
    while (1)
    {
        product--;      //消费产品
        printf("Consumer product,  stock product: %d\n", product);
        sleep(1);       //模拟时间消耗

        /*切换到其他任务*/
        yeild();    
    }
}

int main(int unused1, char **unused2)
{
    /*创建生产者消费者任务协程*/
    producer_task = task_creat(producer, 4096);
    consumer_task = task_creat(consumer, 4096);

    while (1)
    {
        /*恢复任务至运行态*/
        resume(producer_task);
        printf("Coroutine Task swtich+++\n");
        resume(consumer_task);
        printf("Coroutine Task swtich---\n");
    }

    return 0;
}
