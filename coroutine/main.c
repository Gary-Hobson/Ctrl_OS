/*
 * @Author: Hobson
 * @Date: 2021-03-17 12:55:13
 * @Description: ʹ��Э��ʵ��������������
 * @LastEditTime: 2021-03-18 23:01:03
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

/*������*/
void consumer(void *arg)
{
    int cnt = 0;
    while (1)
    {
        product--;      //���Ѳ�Ʒ
        printf("Consumer product,  stock product: %d\n", product);
        sleep(1);       //ģ��ʱ������

        /*�л�����������*/
        yeild();    
    }
}

int main(int unused1, char **unused2)
{
    /*��������������������Э��*/
    producer_task = task_creat(producer, 4096);
    consumer_task = task_creat(consumer, 4096);

    while (1)
    {
        /*�ָ�����������̬*/
        resume(producer_task);
        printf("Coroutine Task swtich+++\n");
        resume(consumer_task);
        printf("Coroutine Task swtich---\n");
    }

    return 0;
}
