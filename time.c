

#include "codexion.h"

struct	timespec get_abs_time(long long cooldown)
{
	struct	timespec	abs_time;
	long long			target_ms;

	//milliseconds
	target_ms = cooldown;
	//seconds (divide by 1000)
	abs_time.tv_sec = target_ms / 1000;
	//nanoseconds (* 1,000,000)
	abs_time.tv_nsec = (target_ms % 1000) * 1000000;
	return abs_time;
}


long long get_time_ms(void)
{
    struct timeval  tv;

    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000LL) + (tv.tv_usec / 1000LL));
}

long long get_now_time(t_coder *coder)
{
	return (get_time_ms() - coder->system->start_time_ms);
}


int is_wait_time(long long start_time, long long wait_time)
{
    return ((get_time_ms() - start_time) < wait_time);
}

void safe_sleep(long long wait_time)
{
    long long   start_time;

    start_time = get_time_ms();
    while (is_wait_time(start_time, wait_time))
        usleep(500);
}