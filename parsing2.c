#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int is_digit(int c)
{
	if (c <= '9' && c >= '0')
		return (1);
	return (0);
}

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
	if (!(strcmp(scheduler, "edf") && strcmp(scheduler, "fifo"))) 
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


int main(int argc, char **argv)
{

	if (is_valid_number(argv[1]))
		printf("It Works!");
	else
		printf("It Works 2!");





}