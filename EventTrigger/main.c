/*
 * @Author: Hobson
 * @Date: 2021-03-25 13:41:51
 * @Description: 
 * @LastEditTime: 2021-03-29 13:57:16
 */

#include "task.h"
#include "message.h"

#include <unistd.h>

uint16_t product = 0;
/*定义两个任务句柄*/
task_t producer_task, consumer_task;

/*生产者*/
void producer(void *arg)
{
    while (1)
    {
        product += 2; //生产产品

        printf("manefaceture product,  stock product: %d\n", product);
        sleep(1); //模拟时间消耗

        publish_message("product", NULL, 0);
        /*切换到其他任务*/
        yeild();
    }
}

/*消费者*/
void consumer(void *arg)
{
    while (1)
    {
        if (product <= 0)
        {
            printf("无库存，等待生产\n");
            yeild();
        }
        
        product--; //消费产品
        printf("Consumer product,  stock product: %d\n", product);
        sleep(1); //模拟时间消耗
        /*切换到其他任务*/
       
    }
}

int main(int argc, char *argv[])
{
    /*创建生产者消费者任务协程*/
    producer_task = task_creat(producer, 4096);
    task_set_name(producer_task, "producer");
    consumer_task = task_creat(consumer, 4096);
    task_set_name(consumer_task, "consumer");

    subscribe_message("product",consumer_task, 0);
    while (1)
    {
        /*运行任务调度器*/
        task_schedule();
    }

    return 0;
}
