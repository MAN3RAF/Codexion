

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

void swap(t_heap *heap)
{
    t_node  temp;
    
    temp = heap->heap[0];
    heap->heap[0] = heap->heap[1];
    heap->heap[1] = temp;
}


void handle_heap(t_coder *coder, t_dongle *dongle)
{
    long long   deadline_1;
    long long   deadline_2;
    long long   request_time_1;
    long long   request_time_2;

    if (!dongle->min_heap.heap[0].coder_id)
        write_heap(coder, &dongle->min_heap, 0);
    else
        write_heap(coder, &dongle->min_heap, 1);
    deadline_1 = dongle->min_heap.heap[1].deadline;
    deadline_2 = dongle->min_heap.heap[0].deadline;
    request_time_1 = dongle->min_heap.heap[0].request_time;
    request_time_2 = dongle->min_heap.heap[1].request_time;
    if (!strcmp(coder->system->scheduler, "edf")
        && dongle->min_heap.heap[1].coder_id == coder->id)
    {
        if (deadline_1 < deadline_2)
            swap(&dongle->min_heap);
        if (deadline_1 == deadline_2)
            if (request_time_1 > request_time_2)
                swap(&dongle->min_heap);
    }
}


void hold_dongle(t_coder *coder, t_dongle *dongle)
{
    long long           cooldown;
    struct  timespec    abs_time;

    pthread_mutex_lock(&dongle->dongle_lock);
    cooldown = dongle->last_dropped_time + coder->system->dongle_cooldown;
    abs_time = get_abs_time(cooldown);
    handle_heap(coder, dongle);
    while (coder->id != dongle->min_heap.heap[0].coder_id 
        || dongle->owner_id 
        || get_time_ms() < cooldown)
    {
        if (dongle->owner_id)
            pthread_cond_wait(&dongle->waiting_room, &dongle->dongle_lock);
        else
            pthread_cond_timedwait(&dongle->waiting_room,
                &dongle->dongle_lock, &abs_time);
        cooldown = dongle->last_dropped_time + coder->system->dongle_cooldown;
        abs_time = get_abs_time(cooldown);
    }
    // printf("coder %d got the dongle %d\n", coder->id, dongle->dongle_id);//test
    dongle->owner_id = coder->id;
    swap(&dongle->min_heap);
    erase_heap(&dongle->min_heap, 1);
    pthread_mutex_unlock(&dongle->dongle_lock);
}

// void release_dongle()
// {

// }