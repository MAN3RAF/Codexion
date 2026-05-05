

#include "codexion.h"


int is_first_free(t_heap *heap)
{
	if (heap->heap[0].coder_id)
		return 1;
	return 0;
}


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


void erase_heap(t_heap *h, int index)
{
    h->heap[index].coder_id = 0;
    h->heap[index].deadline = 0;
    h->heap[index].request_time = 0;
}


t_dongle *first_and_second(t_coder *coder, int i)
{
	t_dongle *first;
	t_dongle *second;

	if (coder->left_dongle->dongle_id < coder->right_dongle->dongle_id)
    {
        first = coder->left_dongle;
        second = coder->right_dongle;
    }
    if (coder->left_dongle->dongle_id > coder->right_dongle->dongle_id)
    {
        second = coder->left_dongle;
        first = coder->right_dongle;
    }
	if (i == 1)
		return first;
	else
		return second;
}

int is_wait_time(long long start_time, long long wait_time)
{
    return ((get_time_ms() - start_time) < wait_time);
}

// int safe_print(t_coder *coder, int i)
// {

// }