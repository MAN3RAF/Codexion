/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsebar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 08:41:37 by lsebar            #+#    #+#             */
/*   Updated: 2026/05/11 08:41:41 by lsebar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	compile_phase(t_coder *coder)
{
	pthread_mutex_lock(&coder->system->system_lock);
	coder->last_compile = get_time_ms();
	pthread_mutex_unlock(&coder->system->system_lock);
	ft_print(coder, 2);
	if (is_simulation_end(coder))
		return ;
	safe_sleep(coder->system->time_to_compile);
	if (is_simulation_end(coder))
		return ;
	release_dongle(coder->first);
	release_dongle(coder->second);
	pthread_mutex_lock(&coder->system->system_lock);
	coder->times_compiled += 1;
	pthread_mutex_unlock(&coder->system->system_lock);
	debugging_phase(coder);
	refactoring_phase(coder);
}

void	debugging_phase(t_coder *coder)
{
	ft_print(coder, 3);
	if (is_simulation_end(coder))
		return ;
	safe_sleep(coder->system->time_to_debug);
	if (is_simulation_end(coder))
		return ;
}

void	refactoring_phase(t_coder *coder)
{
	ft_print(coder, 4);
	if (is_simulation_end(coder))
		return ;
	safe_sleep(coder->system->time_to_refactor);
	if (is_simulation_end(coder))
		return ;
}
