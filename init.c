/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsebar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 15:51:54 by lsebar            #+#    #+#             */
/*   Updated: 2026/04/25 15:51:54 by lsebar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"


int coder_init(t_system *system)
{
    int         i;

    system->coders = malloc(sizeof(t_coder) * system->number_of_coders);
    if (!system->coders)
        return (1);
	i = 0;
    while (i < system->number_of_coders)
    {
        system->coders[i].id = i + 1;
        system->coders[i].system = system;
        pthread_create(&system->coders[i].thread_id,
            NULL, coder_routine, &system->coders[i]);
        i++;
    }
    i = 0;
    while (i < system->number_of_coders)
    {
        pthread_join(system->coders[i].thread_id, NULL);
        i++;
    }
    return (0);
}


void system_init(t_system *system, char **argv)
{
    system->number_of_coders = atoi(argv[1]);
    system->time_to_burnout = atoi(argv[2]);
    system->time_to_compile = atoi(argv[3]);
    system->time_to_debug = atoi(argv[4]);
    system->time_to_refactor = atoi(argv[5]);
    system->number_of_compiles_required = atoi(argv[6]);
    system->dongle_cooldown = atoi(argv[7]);
    system->scheduler = argv[8];
	
}


int data_init(t_system *system, char **argv)
{
    system_init(system, argv);
    coder_init(system);
    return 0;
}