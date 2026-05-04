

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

void hold_dongle(t_coder *coder)
{
    size_t  cooldown;

    cooldown = get_time_ms() - coder->right_dongle->last_dropped_time;
    pthread_mutex_lock(&coder->right_dongle->dongle_lock);
    if (!coder->right_dongle->min_heap.heap[1].coder_id)
        coder->right_dongle->min_heap.heap[1].coder_id;
    


    while (!coder->id == coder->right_dongle->min_heap.heap[1].coder_id
        || coder->right_dongle->min_heap.heap->coder_id 
        || cooldown < coder->system->dongle_cooldown)
    {

        if (coder->right_dongle->owner_id)
            pthread_cond_wait(&coder->right_dongle->waiting_room, &coder->right_dongle->dongle_lock);



    }


    pthread_mutex_unlock(&coder->right_dongle->dongle_lock);

}

// void release_dongle()
// {

// }