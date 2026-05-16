/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsebar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 08:40:06 by lsebar            #+#    #+#             */
/*   Updated: 2026/05/16 15:50:18 by lsebar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	free_dongles(t_system *system)
{
	int	i;

	i = 0;
	destroy_dongles_cond(system);
	while (i < system->number_of_coders)
	{
		if (system->dongles[i].min_heap.heap)
			free(system->dongles[i].min_heap.heap);
		i++;
	}
	pthread_cond_destroy(&system->dongles->waiting_room);
	free(system->dongles);
}

void	destroy_dongles_cond(t_system *system)
{
	int	i;

	i = 0;
	while (i < system->number_of_coders)
	{
		pthread_cond_destroy(&system->dongles->waiting_room);
		i++;
	}
}

void	destroy_dongles_mutexes(t_system *system)
{
	int	i;

	i = 0;
	while (i < system->number_of_coders)
	{
		pthread_mutex_destroy(&system->dongles[i].dongle_lock);
		i++;
	}
}

void	destroy_coders_mutexes(t_system *system)
{
	int	i;

	i = 0;
	while (i < system->number_of_coders)
	{
		pthread_mutex_destroy(&system->coders[i].coder_lock);
		i++;
	}
}

void	clean(t_system *system)
{
	destroy_dongles_mutexes(system);
	destroy_coders_mutexes(system);
	free_system(system);
	free_dongles(system);
	free(system->coders);
}
