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



int main(int argc, char **argv)
{
    t_system system;

    // if (DEBUGGING == 1)
    //     write(1, "Good!\n", 6);

    if (parse_input(argc, argv))
        return 1;

    data_init(&system, argv);

    // if (DEBUGGING == 1)
    //     write(1, "Good!\n", 6);

    start_simulation(&system);


}

