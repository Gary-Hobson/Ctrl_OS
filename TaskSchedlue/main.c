/*
 * @Author: Hobson
 * @Date: 2021-03-17 12:55:13
 * @Description: 使用协程实现生产者消费者
 * @LastEditTime: 2021-03-23 23:04:55
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

int foo(int b)
{
    int a = 1;
    a = a + b;
    return a;
}

/*消费者*/
void consumer(void *arg)
{
    while (1)
    {
        if (product>=5)
        {
            break;
        }

        product--; //消费产品
        printf("Consumer product,  stock product: %d\n", product);
        sleep(1);       //模拟时间消耗
        foo(1);
        /*切换到其他任务*/
        yeild();
    }
}

int main(int argc, char *argv[])
{
    /*创建生产者消费者任务协程*/
    producer_task = task_creat(producer, 4096);
    task_set_name(producer_task, "producer");
    consumer_task = task_creat(consumer, 4096);
    task_set_name(consumer_task, "consumer");

    while (1)
    {
        /*运行任务调度器*/
        task_schedule();
    }

    return 0;
}
