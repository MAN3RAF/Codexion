/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsebar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 08:41:21 by lsebar            #+#    #+#             */
/*   Updated: 2026/05/11 08:40:42 by lsebar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	start_simulation(t_system *system)
{
	int	i;

	pthread_mutex_lock(&system->start_lock);
	system->start_time_ms = get_time_ms();
	system->all_threads_ready = true;
	pthread_cond_broadcast(&system->start_line);
	pthread_mutex_unlock(&system->start_lock);
	i = 0;
	while (i < system->number_of_coders)
	{
		pthread_join(system->coders[i].thread, NULL);
		i++;
	}
	pthread_join(system->monitor, NULL);
}

void	*coder_routine(void *arg)
{
	t_coder		*coder;
	long long	time;

	coder = (t_coder *)arg;
	pthread_mutex_lock(&coder->system->start_lock);
	while (!coder->system->all_threads_ready)
		pthread_cond_wait(&coder->system->start_line,
			&coder->system->start_lock);
	pthread_mutex_unlock(&coder->system->start_lock);
	time = get_now_time(coder);
	if (coder->id % 2 == 0)
		safe_sleep(1);
	while (1)
	{
		if (is_simulation_end(coder))
			break ;
		if (is_compiled_enough(coder))
			break ;
		hold_dongle(coder, coder->first);
		hold_dongle(coder, coder->second);
		compile_phase(coder);
	}
	return (NULL);
}
