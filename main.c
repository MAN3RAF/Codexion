/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsebar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 15:51:54 by lsebar            #+#    #+#             */
/*   Updated: 2026/04/25 15:51:54 by lsebar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void start_simulation(t_system *system)
{
    pthread_mutex_lock(&system->start_lock);
    system->start_time_ms = get_time_ms(); // The true T=0
    system->all_threads_ready = true;      // Open the gates!
    pthread_cond_broadcast(&system->start_line); // Wake everyone up!
    pthread_mutex_unlock(&system->start_lock);
}

int main(int argc, char **argv)
{
    t_system system;

    if (DEBUGGING == 1)
    {
        write(1, "DEBUGGING MODE ON!\n", 19);
    }

    if (parse_input(argc, argv))
        return 1;

    data_init(&system, argv);

    start_simulation(&system);

    // if (DEBUGGING == 1)
    // {
    //     write(1, "11!\n", 19);
    // }

}

