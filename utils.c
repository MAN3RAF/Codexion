

#include "codexion.h"


// int is_first_free(t_heap *heap)
// {
// 	if (heap->heap[0].coder_id)
// 		return 1;
// 	return 0;
// }


void wake_up(t_system *system) //wake up all sleeping Beauties!
{
	int	i;

	i = 0;
	while (i < system->number_of_coders)
	{
		pthread_cond_broadcast(&system->coders[i].first->waiting_room);
		pthread_cond_broadcast(&system->coders[i].second->waiting_room);
		i++;
	}
}

int is_compiled_enough(t_coder *coder)
{
	int i;

	i = 0;
	pthread_mutex_lock(&coder->coder_lock);
	if (coder->times_compiled >= coder->system->number_of_compiles_required)
		i = 1;
	pthread_mutex_unlock(&coder->coder_lock);
	return i;
}



void	ft_putstr(char *s)
{
	if (!s)
		return ;
	while (*s)
	{
		write(1, s, 1);
		s++;
	}
}


t_dongle *first_and_second(t_coder *coder, int i)
{
	t_dongle *first;
	t_dongle *second;

	if (coder->left_dongle->dongle_id < coder->right_dongle->dongle_id)
    {
        first = coder->left_dongle;
        second = coder->right_dongle;
    }
    if (coder->left_dongle->dongle_id > coder->right_dongle->dongle_id)
    {
        second = coder->left_dongle;
        first = coder->right_dongle;
    }
	if (i == 1)
		return first;
	else
		return second;
}



// int safe_print(t_coder *coder, int i)
// {

// }