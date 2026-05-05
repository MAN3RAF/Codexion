

#include "codexion.h"

void compile_phase(t_coder *coder)
{
    // have to check if not end_simulation or somemeone burnedout!

    pthread_mutex_lock(&coder->coder_lock);
    coder->last_compile = get_time_ms();
    pthread_mutex_unlock(&coder->coder_lock);

    pthread_mutex_lock(&coder->system->print_lock);
    printf("%lld %d coder is compiling", get_time_ms(), coder->id);
    pthread_mutex_unlock(&coder->system->print_lock);

    safe_sleep(coder->system->time_to_compile);

    // drop_dongle(coder->first);
    // drop_dongle(coder->second);

    pthread_mutex_lock(&coder->coder_lock);
    coder->times_compiled += 1;
    pthread_mutex_unlock(&coder->coder_lock);

    debugging_phase(coder);
    refactoring_phase(coder);
}

void debugging_phase(t_coder *coder)
{
    // have to check if not end_simulation or somemeone burnedout!

    pthread_mutex_lock(&coder->system->print_lock);
    printf("%lld %d coder is debigging", get_time_ms(), coder->id);
    pthread_mutex_unlock(&coder->system->print_lock);

    safe_sleep(coder->system->time_to_debug);
}

void refactoring_phase(t_coder *coder)
{
    // have to check if not end_simulation or somemeone burnedout!

    pthread_mutex_lock(&coder->system->print_lock);
    printf("%lld %d coder is refactoring", get_time_ms(), coder->id);
    pthread_mutex_unlock(&coder->system->print_lock);

    safe_sleep(coder->system->time_to_refactor);
}

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
