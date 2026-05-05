

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
