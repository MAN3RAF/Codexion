

#include "codexion.h"

// int is_owned(t_dongle *dongle)
// {
// 	int	i;

// 	i = 0;
// 	pthread_mutex_lock(&dongle->dongle_lock);
// 	if (dongle->owner_id)
// 		i = 1;
// 	pthread_mutex_unlock(&dongle->dongle_lock);
// 	return i;
// }

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
        if (is_simulation_end(coder))
            break;
        if (dongle->owner_id)
            pthread_cond_wait(&dongle->waiting_room, &dongle->dongle_lock);
        else
            pthread_cond_timedwait(&dongle->waiting_room,
                &dongle->dongle_lock, &abs_time);
        cooldown = dongle->last_dropped_time + coder->system->dongle_cooldown;
        abs_time = get_abs_time(cooldown);
    }
    dongle->owner_id = coder->id;
    swap(&dongle->min_heap);
    erase_heap(&dongle->min_heap, 1);
	ft_print(coder, dongle, 1);
    pthread_mutex_unlock(&dongle->dongle_lock);
}

void release_dongle(t_dongle *dongle)
{
    pthread_mutex_lock(&dongle->dongle_lock);
    dongle->last_dropped_time = get_time_ms();
    // printf("%d has released dongle %d\n", dongle->owner_id, dongle->dongle_id);
    dongle->owner_id = 0;
    pthread_cond_broadcast(&dongle->waiting_room);
    pthread_mutex_unlock(&dongle->dongle_lock);
}