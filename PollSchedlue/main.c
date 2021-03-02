#include "PollSchedule.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <stdio.h>
 
/*时间触发用户结构体*/
struct time_task
{
    uint32_t last_time;     //上次执行时间
    uint32_t interval;      //执行间隔
    enum TIME_MODE flag;        //执行模式
};

/*定义时间检测函数*/
int check_time(void *arg)
{
    uint32_t current_time=millis();
    if(current_time - ((struct time_task *)arg)->last_time > ((struct time_task *)arg)->interval)
    {
        ((struct time_task *)arg)->last_time=current_time;
        return 1;
    }

    return 0;
}

/*定义时间触发参数结构体*/
struct time_task task_1s={0,1000,0};

/*非阻塞读取按键状态，一次返回一字节，具有缓存功能*/
int read_key()
{
    int input,res;
    struct termios new_settings;
    struct termios stored_settings;
    tcgetattr(0,&stored_settings);
    new_settings = stored_settings;
    new_settings.c_lflag &= (~ICANON);
    new_settings.c_cc[VTIME] = 0;
    tcgetattr(0,&stored_settings);
    new_settings.c_cc[VMIN] = 0;        //0为非阻塞读取，1为阻塞读取
    tcsetattr(0,TCSANOW,&new_settings);
      
    res = read(0,&input,1);  
    if(res == 0)
    {
        input = 0;
    }
    tcsetattr(0,TCSANOW,&stored_settings);
    return input;
}

/*按键检测判断*/
int check_key(void *arg)
{
    static char key_buf[256]={0};

    key_buf[read_key()]=1;

    if(key_buf[(long)arg]==1)
    {
        key_buf[(long)arg]=0;
        return 1;
    }

    return 0;
}

/*按键触发处理函数*/
void key_trigger(void *arg)
{
    printf("Tick :%d, key :'%c' trigger \n", millis(),arg);
}

/*定时任务*/
void Timed_Task(void *arg)
{
    printf("Tick :%d, %d\n", millis(),arg);
}

void setup(void)
{
    /*注册按键触发任务*/
    poll_task_register(check_key, key_trigger, (void *)'c');
    poll_task_register(check_key, key_trigger, (void *)'0');
    
    /*注册时间触发任务*/
    poll_task_register(check_time, Timed_Task, &task_1s);
}

int main(int argc, char * argv[])
{
    setup();
    
    while (1)
    {
        /*执行轮询调度器*/
        poll_task_schedule();
    }

}
