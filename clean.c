


#include "codexion.h"


void free_dongles(t_system *system)
{
	int	i;

	i = 0;
	while (i < system->number_of_coders)
	{
		free(system->dongles[i].min_heap.heap);
		i++;
	}
	free(system->dongles);
}

void destroy_dongles_mutexes(t_system *system)
{
	int	i;

	i = 0;
	while (i < system->number_of_coders)
	{
		pthread_mutex_destroy(&system->dongles[i].dongle_lock);
		i++;
	}
}

void destroy_coders_mutexes(t_system *system)
{
	int	i;

	i = 0;
	while (i < system->number_of_coders)
	{
		pthread_mutex_destroy(&system->coders[i].coder_lock);
		i++;
	}
}

void destroy_system_mutexes(t_system *system)
{
	pthread_mutex_destroy(&system->system_lock);
	pthread_mutex_destroy(&system->print_lock);
	pthread_mutex_destroy(&system->start_lock);
}


void clean(t_system *system)
{
	// destroy all mutexes!
	// do func to free if a burn out!
	// do func to free if the dongles!
	// do func to free the coders!

	destroy_dongles_mutexes(system);
	destroy_coders_mutexes(system);
	destroy_system_mutexes(system);
	free_dongles(system);
	free(system->coders);
}