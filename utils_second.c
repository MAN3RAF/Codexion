

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


void erase_heap(t_heap *h, int i)
{
    h->heap[i].coder_id = 0;
    h->heap[i].deadline = 0;
    h->heap[i].request_time = 0;
}

