/*
 * @Author: Hobson
 * @Date: 2021-03-17 12:55:13
 * @Description: ʹ��Э��ʵ��������������
 * @LastEditTime: 2021-03-23 23:04:55
 */

#include "task.h"
#include <unistd.h>
#include <stdio.h>

/*����Ʒ����*/
uint16_t product = 0;

/*��������������*/
task_t producer_task, consumer_task;

/*������*/
void producer(void *arg)
{
    while (1)
    {
        product += 2;   //������Ʒ

        printf("manefaceture product,  stock product: %d\n", product);
        sleep(1);       //ģ��ʱ������
        
        /*�л�����������*/
        yeild();
    }
}

int foo(int b)
{
    int a = 1;
    a = a + b;
    return a;
}

/*������*/
void consumer(void *arg)
{
    while (1)
    {
        if (product>=5)
        {
            break;
        }

        product--; //���Ѳ�Ʒ
        printf("Consumer product,  stock product: %d\n", product);
        sleep(1);       //ģ��ʱ������
        foo(1);
        /*�л�����������*/
        yeild();
    }
}

int main(int argc, char *argv[])
{
    /*��������������������Э��*/
    producer_task = task_creat(producer, 4096);
    task_set_name(producer_task, "producer");
    consumer_task = task_creat(consumer, 4096);
    task_set_name(consumer_task, "consumer");

    while (1)
    {
        /*�������������*/
        task_schedule();
    }

    return 0;
}
