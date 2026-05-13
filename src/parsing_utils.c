/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsebar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 09:32:28 by lsebar            #+#    #+#             */
/*   Updated: 2026/05/11 08:42:56 by lsebar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	is_digit(int c)
{
	if (c <= '9' && c >= '0')
		return (1);
	return (0);
}

int	check_is_digit(char *digits)
{
	size_t	i;

	i = 0;
	while (i < strlen(digits))
	{
		if (!is_digit(digits[i]))
			return (1);
		i++;
	}
	return (0);
}
