


#include "codexion.h"


void clean(t_system *system)
{
	int	i;

	i = 0;
	while (i < system->number_of_coders)
	{
		free(system->dongles[i].min_heap.heap);
		
		i++;
	}
	i = 0;


	// destroy all mutexes!
	// do func to free if a burn out!
	// do func to free if the dongles!
	// do func to free the coders!

	while (i < system->number_of_coders)
	{

	}

	free(&system->dongles);
	free(&system->coders);


}