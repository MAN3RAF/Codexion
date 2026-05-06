



#include "codexion.h"


void print(t_coder *coder, int i)
{
	static int	burned_out;

	// have to check if static var is 1 dont print!
	if (i == 1)
	{
		pthread_mutex_lock(&coder->system->print_lock);
    	printf("%lld %d coder is compiling\n", get_now_time(coder), coder->id);
    	pthread_mutex_unlock(&coder->system->print_lock);
	}
	else if (i == 2)
	{
		pthread_mutex_lock(&coder->system->print_lock);
    	printf("%lld %d coder is debigging\n", get_now_time(coder), coder->id);
    	pthread_mutex_unlock(&coder->system->print_lock);
	}
	else if (i == 3)
	{
		pthread_mutex_lock(&coder->system->print_lock);
	    printf("%lld %d coder is refactoring , compiled: %d\n", get_now_time(coder), coder->id, coder->times_compiled);
    	pthread_mutex_unlock(&coder->system->print_lock);
	}
	else if (i == 4)
	{
		//have to set static var to a value!
		pthread_mutex_lock(&coder->system->print_lock);
    	write(1, get_now_time(coder), 1);
		write(1, coder->id, 1);
		write(1, "burned out\n", 11);
    	pthread_mutex_unlock(&coder->system->print_lock);
	}


}



void *monitor(void *arg)
{
	t_system *system;
	t_coder coder;
	int	i;

	system = (t_system *)arg;
	i = 0;
	while (1)
	{
		coder = system->coders[i];
		if ((get_time_ms() - coder.last_compile) > system->time_to_burnout 
			&& coder.times_compiled != system->number_of_compiles_required)
		{	
			print(coder, 4);
			break;
			// print func!
		}
		i++;
		i = i % system->number_of_coders;

	}
	return NULL;
}