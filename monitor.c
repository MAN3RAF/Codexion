



#include "codexion.h"

void ft_print_utils(t_coder *coder, int choice, int burned_out)
{
	if (choice == 2 && !burned_out)
	{
		pthread_mutex_lock(&coder->system->print_lock);
    	printf("%lld %d coder is compiling\n", get_now_time(coder), coder->id);
    	pthread_mutex_unlock(&coder->system->print_lock);
	}
	else if (choice == 3 && !burned_out)
	{
		pthread_mutex_lock(&coder->system->print_lock);
    	printf("%lld %d coder is debigging\n", get_now_time(coder), coder->id);
    	pthread_mutex_unlock(&coder->system->print_lock);
	}
	else if (choice == 4 && !burned_out)
	{
		pthread_mutex_lock(&coder->system->print_lock);
	    printf("%lld %d coder is refactoring , compiled: %d\n", 
			get_now_time(coder), coder->id, coder->times_compiled);
    	pthread_mutex_unlock(&coder->system->print_lock);
	}

}

void ft_print(t_coder *coder, t_dongle *dongle, int choice)
{
	static int	burned_out;
	long long	time;

	time = get_now_time(coder);
	if (choice == 1 && !burned_out)
	{
		pthread_mutex_lock(&coder->system->print_lock);
    	printf("%lld %d has taken a dongle %d , compiled: %d\n", time,
			 coder->id, dongle->dongle_id, coder->times_compiled);
    	pthread_mutex_unlock(&coder->system->print_lock);
	}
	else if (choice == 5 && !burned_out)
	{
		burned_out = 1;
		pthread_mutex_lock(&coder->system->print_lock);
		printf("%lld %d burtned out\n", time, coder->id);
    	pthread_mutex_unlock(&coder->system->print_lock);
	}
	else
		ft_print_utils(coder, choice, burned_out);
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
			system->end_simulation = true;
			ft_print(&system->coders[i], NULL, 5);
			// write(1, "SOMEONE BURNED OUT!!!!!!\n", 25);
			break;
			// print func!
		}
		i++;
		i = i % system->number_of_coders;

	}
	return NULL;
}