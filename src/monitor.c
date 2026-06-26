/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsebar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 08:42:32 by lsebar            #+#    #+#             */
/*   Updated: 2026/05/11 08:42:34 by lsebar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	is_simulation_end(t_coder *coder)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&coder->system->system_lock);
	if (coder->system->end_simulation)
		i = 1;
	pthread_mutex_unlock(&coder->system->system_lock);
	return (i);
}

void	ft_print_utils(t_coder *coder, int choice, int burned_out)
{
	if (choice == 2 && !burned_out)
		printf("%lld %d is compiling\n", get_now_time(coder), coder->id);
	else if (choice == 3 && !burned_out)
		printf("%lld %d is debugging\n", get_now_time(coder), coder->id);
	else if (choice == 4 && !burned_out)
		printf("%lld %d is refactoring\n", get_now_time(coder),
			coder->id);
}

void	ft_print(t_coder *coder, int choice)
{
	static int	burned_out;
	long long	time;

	pthread_mutex_lock(&coder->system->print_lock);
	time = get_now_time(coder);
	if (choice == 1 && !burned_out)
		printf("%lld %d has taken a dongle\n", time, coder->id);
	else if (choice == 5 && !burned_out)
	{
		burned_out = 1;
		printf("%lld %d burned out\n", time, coder->id);
	}
	else
		ft_print_utils(coder, choice, burned_out);
	pthread_mutex_unlock(&coder->system->print_lock);
}

int	burned_out(t_system *system, int i, int counter)
{
	t_coder	*coder;

	while (1)
	{
		if (i == 0)
			counter = 0;
		coder = &system->coders[i];
		pthread_mutex_lock(&coder->coder_lock);
		if ((get_time_ms() - coder->last_compile) > system->time_to_burnout
			&& coder->times_compiled < system->number_of_compiles_required)
		{
			pthread_mutex_unlock(&coder->coder_lock);
			end_simulation(system, coder);
			return (1);
		}
		if (coder->times_compiled >= system->number_of_compiles_required)
			counter++;
		pthread_mutex_unlock(&coder->coder_lock);
		if (counter == system->number_of_coders)
			break ;
		i++;
		i = i % system->number_of_coders;
	}
	return (0);
}

void	*monitor(void *arg)
{
	t_system	*system;
	int			i;
	int			counter;

	system = (t_system *)arg;
	i = 0;
	counter = 0;
	pthread_mutex_lock(&system->start_lock);
	while (!system->all_threads_ready)
		pthread_cond_wait(&system->start_line, &system->start_lock);
	pthread_mutex_unlock(&system->start_lock);
	if (!burned_out(system, i, counter))
		return (NULL);
	wake_up(system);
	return (NULL);
}
