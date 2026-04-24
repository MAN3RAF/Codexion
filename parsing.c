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
#include <pthread.h>
#include <string.h>
#include <unistd.h>






int main(int argc, char **argv)
{
	int i;
	int number_of_coders;
	int time_to_burnout;
	int time_to_compile;
	int time_to_debug;
	int time_to_refactor;
	int number_of_compiles_required;
	int dongle_cooldown;
	char *scheduler;

	//if user gives nothing?
	//if user gives 1 or 2 but the rest nothing?

	if (atoi(argv[1]) && atoi(argv[1]) != 0)
		number_of_coders = atoi(argv[1]);

	else
	{
		number_of_coders = 0;
		printf("Invalid numbuer_of_coders");
	}

	if (atoi(argv[2]) && atoi(argv[2]) != 0)
		time_to_burnout = atoi(argv[2]);
	
	else
	{
		time_to_burnout = 0;
		printf("Invalid time_to_burnout");
	}

	if (atoi(argv[3]) && atoi(argv[3]) != 0)
		time_to_compile = atoi(argv[3]);
	
	else
	{
		time_to_compile = 0;
		printf("Invalid time_to_compile");
	}

	if (atoi(argv[4]) && atoi(argv[4]) != 0)
		time_to_debug = atoi(argv[4]);
	
	else
	{
		time_to_debug = 0;
		printf("Invalid time_to_debug");
	}

	if (atoi(argv[5]) && atoi(argv[5]) != 0)
		time_to_refactor = atoi(argv[5]);
	
	else
	{
		time_to_refactor = 0;
		printf("Invalid time_to_refactor");
	}

	if (atoi(argv[6]) && atoi(argv[6]) != 0)
		number_of_compiles_required = atoi(argv[6]);
	
	else
	{
		number_of_compiles_required = 0;
		printf("Invalid number_of_compiles_required");
	}

	if (atoi(argv[7]) && atoi(argv[7]) != 0)
		dongle_cooldown = atoi(argv[7]);
	
	else
	{
		dongle_cooldown = 0;
		printf("Invalid dongle_cooldown");
	}

	if (strcmp(argv[8], "edf") || strcmp(argv[8], "fifo"))
		scheduler = argv[8];
	else
		printf("Invalid scheduler");

}

