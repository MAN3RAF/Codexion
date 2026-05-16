/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsebar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 15:51:54 by lsebar            #+#    #+#             */
/*   Updated: 2026/05/11 08:42:20 by lsebar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	dongle_init(t_system *system)
{
	int	i;

	i = 0;
	system->dongles = malloc(sizeof(t_dongle) * system->number_of_coders);
	if (!system->dongles)
		return (1);
	while (i < system->number_of_coders)
	{
		pthread_mutex_init(&system->dongles[i].dongle_lock, NULL);
		pthread_cond_init(&system->dongles[i].waiting_room, NULL);
		system->dongles[i].dongle_id = i;
		system->dongles[i].owner_id = 0;
		system->dongles[i].last_dropped_time = 0;
		system->dongles[i].min_heap.heap = malloc(sizeof(t_node) * 2);
		if (!system->dongles[i].min_heap.heap)
			return (1);
		erase_heap(&system->dongles[i].min_heap, 0);
		erase_heap(&system->dongles[i].min_heap, 1);
		i++;
	}
	return (0);
}

void	threads_init(t_system *system)
{
	int	i;

	i = 0;
	while (i < system->number_of_coders)
	{
		pthread_create(&system->coders[i].thread, NULL, coder_routine,
			&system->coders[i]);
		i++;
	}
	pthread_create(&system->monitor, NULL, monitor, system);
}

int	coder_init(t_system *system)
{
	int	i;

	i = 0;
	system->coders = malloc(sizeof(t_coder) * system->number_of_coders);
	if (!system->coders)
		return (1);
	while (i < system->number_of_coders)
	{
		system->coders[i].id = i + 1;
		system->coders[i].system = system;
		system->coders[i].times_compiled = 0;
		system->coders[i].left_dongle = &system->dongles[i];
		system->coders[i].right_dongle = &system->dongles[(i + 1)
			% system->number_of_coders];
		system->coders[i].first = first_and_second(&system->coders[i], 1);
		system->coders[i].second = first_and_second(&system->coders[i], 2);
		system->coders[i].last_compile = system->start_time_ms;
		pthread_mutex_init(&system->coders[i].coder_lock, NULL);
		i++;
	}
	return (0);
}

void	system_init(t_system *system, char **argv)
{
	system->number_of_coders = atoi(argv[1]);
	system->time_to_burnout = atoi(argv[2]);
	system->time_to_compile = atoi(argv[3]);
	system->time_to_debug = atoi(argv[4]);
	system->time_to_refactor = atoi(argv[5]);
	system->number_of_compiles_required = atoi(argv[6]);
	system->dongle_cooldown = atoi(argv[7]);
	system->scheduler = argv[8];
	system->start_time_ms = get_time_ms();
	system->all_threads_ready = false;
	system->end_simulation = false;
	pthread_cond_init(&system->start_line, NULL);
	pthread_mutex_init(&system->system_lock, NULL);
	pthread_mutex_init(&system->print_lock, NULL);
	pthread_mutex_init(&system->start_lock, NULL);
}

int	data_init(t_system *system, char **argv)
{
	system_init(system, argv);
	if (dongle_init(system))
	{
		if (!system->dongles)
			return (1);
		else
		{
			free_dongles(system);
			free_system(system);
			return (1);
		}
	}
	if (coder_init(system))
	{
		free_dongles(system);
		free_system(system);
		destroy_coders_mutexes(system);
		return (1);
	}
	threads_init(system);
	return (0);
}
