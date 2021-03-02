#include <sys/time.h>
#include <time.h>
#include <stdint.h>

uint32_t millis(void)
{
    // uint64_t tick = clock();
    // return tick *1000 / CLOCKS_PER_SEC;

    struct timeval tm;
    static uint64_t start_time=0;
    gettimeofday(&tm,0);
    if(start_time==0)
    {
        start_time= tm.tv_sec*1000+tm.tv_usec/1000;
    }

    return tm.tv_sec*1000+tm.tv_usec/1000-start_time;

}

