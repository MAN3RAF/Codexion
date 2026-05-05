

#include "codexion.h"

void	*coder_routine(void *arg)
{
	t_coder     *coder;
    long long   time;

    pthread_mutex_lock(&coder->system->start_lock);
    while (!coder->system->all_threads_ready)
    {    
        pthread_cond_wait(&coder->system->start_line, &coder->system->start_lock);
    }
    pthread_mutex_unlock(&coder->system->start_lock);

    // the idea here is to make all the threads wait for others to group up and enter together!


    coder = (t_coder *)arg;
    time = get_time_ms() - coder->system->start_time_ms;
    if (coder->id % 2 == 0)
        safe_sleep(coder->system->number_of_compiles_required);
    while(1)
    {
        pthread_mutex_lock(&coder->system->system_lock);
        if (coder->system->end_simulation)
        {
            pthread_mutex_unlock(&coder->system->system_lock);
            break;
        }
        pthread_mutex_unlock(&coder->system->system_lock);
        pthread_mutex_lock(&coder->coder_lock);
        if (coder->times_compiled > coder->system->number_of_compiles_required)
        {
            pthread_mutex_unlock(&coder->coder_lock);
            break;
        }
        pthread_mutex_unlock(&coder->coder_lock);
        hold_dongle(coder, coder->first); //test
        hold_dongle(coder, coder->second); //test
        compile_phase(coder);
    }
    return (NULL);
}
