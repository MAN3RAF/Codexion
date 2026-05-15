/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsebar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 08:41:53 by lsebar            #+#    #+#             */
/*   Updated: 2026/05/11 08:41:57 by lsebar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	own_dongle(t_coder *coder, t_dongle *dongle)
{
	dongle->owner_id = coder->id;
	swap_heap(&dongle->min_heap);
	erase_heap(&dongle->min_heap, 1);
	ft_print(coder, 1);
}

void	hold_dongle(t_coder *coder, t_dongle *dongle)
{
	long long		cooldown;
	struct timespec	abs_time;

	pthread_mutex_lock(&dongle->dongle_lock);
	cooldown = dongle->last_dropped_time + coder->system->dongle_cooldown;
	abs_time = get_abs_time(cooldown);
	handle_heap(coder, dongle);
	while (coder->id != dongle->min_heap.heap[0].coder_id || dongle->owner_id
		|| get_time_ms() < cooldown)
	{
		if (is_simulation_end(coder))
		{
			pthread_mutex_unlock(&dongle->dongle_lock);
			return ;
		}
		if (dongle->owner_id)
			pthread_cond_wait(&dongle->waiting_room, &dongle->dongle_lock);
		else
			pthread_cond_timedwait(&dongle->waiting_room, &dongle->dongle_lock,
				&abs_time);
		cooldown = dongle->last_dropped_time + coder->system->dongle_cooldown;
		abs_time = get_abs_time(cooldown);
	}
	own_dongle(coder, dongle);
	pthread_mutex_unlock(&dongle->dongle_lock);
}

void	release_dongle(t_dongle *dongle)
{
	pthread_mutex_lock(&dongle->dongle_lock);
	dongle->last_dropped_time = get_time_ms();
	dongle->owner_id = 0;
	pthread_cond_broadcast(&dongle->waiting_room);
	pthread_mutex_unlock(&dongle->dongle_lock);
}
