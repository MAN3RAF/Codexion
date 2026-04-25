/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsebar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 16:57:41 by lsebar            #+#    #+#             */
/*   Updated: 2026/04/24 16:57:44 by lsebar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int check_str_greather_intmax(const char *s)
{
	int		s_len;
	int		intmax_len;
	char	*intmax;

	intmax = "2147483647";
	intmax_len = strlen(intmax);
	s_len = strlen(s);

	if (s_len > intmax_len)
		return 1;
	else if (s_len < intmax_len)
		return 0;
	else
		return strcmp(s, intmax) > 0;
}

char *validate_values_first(int *number_of_coders, int *time_to_burnout,
	int *time_to_compile, char **argv)
{
	if (atoi(argv[1]) && atoi(argv[1]) > 0 &&
	!check_str_greather_intmax(argv[1]))
		*number_of_coders = atoi(argv[1]);
	else
	{
		*number_of_coders = 0;
		printf("Invalid numbuer_of_coders");
		return "1";
	}
	if (atoi(argv[2]) && atoi(argv[2]) > 0 &&
	!check_str_greather_intmax(argv[2]))
		*time_to_burnout = atoi(argv[2]);
	else
	{
		*time_to_burnout = 0;
		printf("Invalid time_to_burnout");
		return "1";
	}
	if (atoi(argv[3]) && atoi(argv[3]) > 0 &&
	!check_str_greather_intmax(argv[3]))
		*time_to_compile = atoi(argv[3]);
	else
	{
		*time_to_compile = 0;
		printf("Invalid time_to_compile");
		return "1";
	}
	return 0;
}

char *validate_values_second(int *time_to_debug, int *time_to_refactor,
	int *number_of_compiles_required, char **argv)
{
	if (atoi(argv[4]) && atoi(argv[4]) > 0 &&
	!check_str_greather_intmax(argv[4]))
			*time_to_debug = atoi(argv[4]);
	else
	{
		*time_to_debug = 0;
		printf("Invalid time_to_debug");
		return "1";
	}
	if (atoi(argv[5]) && atoi(argv[5]) > 0 &&
	!check_str_greather_intmax(argv[5]))
		*time_to_refactor = atoi(argv[5]);
	else
	{
		*time_to_refactor = 0;
		printf("Invalid time_to_refactor");
		return "1";
	}
	if (atoi(argv[6]) && atoi(argv[6]) > 0 &&
	!check_str_greather_intmax(argv[6]))
		*number_of_compiles_required = atoi(argv[6]);
	else
	{
		*number_of_compiles_required = 0;
		printf("Invalid number_of_compiles_required");
		return "1";
	}
	return 0;
}

char *validate_values_third(int *dongle_cooldown, char **scheduler,
	char **argv)
{
	if (atoi(argv[7]) && atoi(argv[7]) > 0 &&
	!check_str_greather_intmax(argv[7]))
		*dongle_cooldown = atoi(argv[7]);
	else
	{
		*dongle_cooldown = 0;
		printf("Invalid dongle_cooldown");
		return "1";
	}
	if (!(strcmp(argv[8], "edf") && strcmp(argv[8], "fifo")))
		*scheduler = argv[8];
	else
	{
		*scheduler = "";
		printf("Invalid scheduler");
		return "1";
	}
	return 0;
}

int main(int argc, char **argv)
{
	int		number_of_coders;
	int		time_to_burnout;
	int		time_to_compile;
	int		time_to_debug;
	int		time_to_refactor;
	int		number_of_compiles_required;
	int		dongle_cooldown;
	char	*scheduler;

	if (argc == 9)
	{
		if (validate_values_first(&number_of_coders, &time_to_burnout,
			&time_to_compile, argv) || validate_values_second(&time_to_debug,
				&time_to_refactor, &number_of_compiles_required, argv) ||
				validate_values_third(&dongle_cooldown, &scheduler, argv))
					return 1;
	}
	else
	{
		printf("The arguments have to be exactly 9 args");
		return 1;
	}
}
