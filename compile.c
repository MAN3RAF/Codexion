

#include "codexion.h"


void compile_phase(t_coder *coder)
{
    // have to check if not end_simulation or somemeone burnedout!

    pthread_mutex_lock(&coder->system->system_lock);
    coder->last_compile = get_time_ms();
    pthread_mutex_unlock(&coder->system->system_lock);

	ft_print(coder, NULL, 2);
    if (is_simulation_end(coder))
        return ;
    safe_sleep(coder->system->time_to_compile);
    if (is_simulation_end(coder))
        return ;
    release_dongle(coder->first);
    release_dongle(coder->second);

    pthread_mutex_lock(&coder->system->system_lock);
    coder->times_compiled += 1;
    pthread_mutex_unlock(&coder->system->system_lock);

    debugging_phase(coder);
    refactoring_phase(coder);
}

void debugging_phase(t_coder *coder)
{
    // have to check if not end_simulation or somemeone burnedout!

    ft_print(coder, NULL, 3);
    if (is_simulation_end(coder))
        return ;
    safe_sleep(coder->system->time_to_debug);
    if (is_simulation_end(coder))
        return ;
}

void refactoring_phase(t_coder *coder)
{
    // have to check if not end_simulation or somemeone burnedout!

    ft_print(coder, NULL, 4);
    if (is_simulation_end(coder))
        return ;
    safe_sleep(coder->system->time_to_refactor);
    if (is_simulation_end(coder))
        return ;
}
