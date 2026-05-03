

#include "codexion.h"

long long get_time_ms(void)
{
    struct timeval  tv;

    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000LL) + (tv.tv_usec / 1000LL));
}


void safe_sleep(long long wait_time)
{
    long long   start_time;

    start_time = get_time_ms();
    while ((get_time_ms() - start_time) < wait_time)
        usleep(500);
}

// void hold_dongle()
// {

// }

// void release_dongle()
// {

// }