



#include "codexion.h"


void *monitor(void *arg)
{
	t_system *system;
	int	i;

	system = (t_system *)arg;
	i = 0;
	while (1)
	{
		if (get_now_time(&system->coders[i]) > system->time_to_burnout)
			printf("COSER %d BURNED OUT!!!!!!!!!!!", system->coders[i].id);

		i++;
		i = i % system->number_of_coders;

	}
	return NULL;
}