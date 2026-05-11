/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsebar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 15:51:54 by lsebar            #+#    #+#             */
/*   Updated: 2026/05/11 08:42:27 by lsebar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	main(int argc, char **argv)
{
	t_system	system;

	if (atoi(argv[1]) == 1)
	{
		printf("Programm can not run with 1 coder!");
		return (1);
	}
	if (parse_input(argc, argv))
		return (1);
	if (data_init(&system, argv))
		return (1);
	start_simulation(&system);
	clean(&system);
}
