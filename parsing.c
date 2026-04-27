#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "codexion.h"


int check_is_digit(char *digits)
{
	int	i;

	i = 0;
	while (i < strlen(digits))
	{
		if (!is_digit(digits[i]))
			return 1;
		i++;
	}
	return 0;
}

int is_valid_scheduler(char *scheduler)
{
	if ((strcmp(scheduler, "edf") && strcmp(scheduler, "fifo"))) 
		return 1;
	return 0;
}

int is_number_greather_intmax(char *s)
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

int is_valid_number(char *s)
{
	if ((check_is_digit(s) || is_number_greather_intmax(s)) || atoi(s) <= 0)
		return 1;
	return 0;
}

int parse_input(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc != 9)
	{
		printf("[ERROR] More or Less than 9 arguments!");
		return 1;
	}
	if (is_valid_scheduler(argv[8]))
	{
		printf("[ERROR] Invalid scheduler: %s", argv[8]);
		return 1;
	}
	while (i < 8)
	{
		if (is_valid_number(argv[i]))
		{
			printf("[ERROR] Invalid argument: %s", argv[i]);
			return 1;
		}
		i++;
	}
}