

#include "codexion.h"

void *coder_routine(void *arg)
{
	t_coder	*coder;

	coder = (t_coder *)arg;
	pthread_mutex_lock(&coder->system->system_lock);
	printf("The coder with the ID %d has been created!", coder->id);
	pthread_mutex_unlock(&coder->system->system_lock);
	return 0;
}