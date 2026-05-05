

#include "codexion.h"

void	*coder_routine(void *arg)
{
	t_coder     *coder;
    t_dongle    *first;
    t_dongle    *second;
    long long   time;

    coder = (t_coder *)arg;
    
    time = get_time_ms() - coder->system->start_time_ms;
	// pthread_mutex_lock(&coder->system->print_lock);
	// printf("%lld The coder with the ID %d has been created!\n", time, coder->id);
	// pthread_mutex_unlock(&coder->system->print_lock); 
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
