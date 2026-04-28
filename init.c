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

void data_init(t_system *system, char **argv)
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
