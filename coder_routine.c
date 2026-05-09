

#include "codexion.h"

void start_simulation(t_system *system)
{
    int i = 0;

    // if (DEBUGGING == 1)
    //     write(1, "Good!\n", 6);

    pthread_mutex_lock(&system->start_lock);
    system->start_time_ms = get_time_ms(); // The true T=0
    system->all_threads_ready = true;      // Open the gates!
    pthread_cond_broadcast(&system->start_line); // Wake everyone up!
    pthread_mutex_unlock(&system->start_lock);

    // if (DEBUGGING == 1)
    // write(1, "Good!\n", 6);

    i = 0;
    while (i < system->number_of_coders)
    {
        pthread_join(system->coders[i].thread, NULL);
        i++;
    }
}


void	*coder_routine(void *arg)
{
	t_coder     *coder;
    long long   time;

    coder = (t_coder *)arg;
    pthread_mutex_lock(&coder->system->start_lock);
    while (!coder->system->all_threads_ready)
        pthread_cond_wait(&coder->system->start_line,&coder->system->start_lock);
    pthread_mutex_unlock(&coder->system->start_lock);
    time = get_now_time(coder);
    if (coder->id % 2 == 0)
        safe_sleep(1); //coder->system->number_of_compiles_required
    while(1)
    {
        if (is_simulation_end(coder))
            break;
        if (is_compiled_enough(coder))
            break;
        hold_dongle(coder, coder->first);
        hold_dongle(coder, coder->second);
        if (DEBUGGING == 1)
            write(1, "before!\n", 8);
        compile_phase(coder);
        if (DEBUGGING == 1)
            write(1, "after!\n", 7);
    }
    return (NULL);
}
