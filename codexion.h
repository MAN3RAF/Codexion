/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsebar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 09:33:05 by lsebar            #+#    #+#             */
/*   Updated: 2026/04/27 09:33:05 by lsebar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
#define CODEXION_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>
#include <sys/time.h>
#include <limits.h>

typedef	pthread_mutex_t t_mutex;
typedef	struct s_system t_system;


//=========Parsing========

int		parse_input(int argc, char **argv);
int		is_valid_number(char *s);
int		is_valid_scheduler(char *scheduler);
int		is_number_greather_intmax(char *s);
int		check_is_digit(char *digits);
int		is_digit(int c);

//=========Init========

int		coder_init(t_system *system);
void	system_init(t_system *system, char **argv);
int		data_init(t_system *system, char **argv);

//=========Routine========

void	*coder_routine(void *arg);










typedef struct s_node
{
	int			coder_id;
	long long	deadline;
	long long	request_time;


}				t_node;


typedef struct s_heap
{
	t_node*	heap;
	int		size;
}				t_heap;


typedef struct s_dongle
{
	t_mutex			dongle_lock;
	int				dongle_id;
	pthread_cond_t	waiting_room;
	int				owner_id;
	long long		last_dropped_time;
	t_heap 			min_heap;

}				t_dongle;


typedef struct s_coder
{
	int			id;
	int			times_compiled;
	int			time_until_burnout;
	long		last_compile;
	t_dongle	*right_dongle;
	t_dongle	*left_dongle;
	pthread_t 	thread_id;
	t_mutex 	coder_lock;
	t_system	*system;

}				t_coder;

typedef struct s_system
{
	int			number_of_coders;
	int			time_to_burnout;
	int			time_to_compile;
	int			time_to_debug;
	int			time_to_refactor;
	int			number_of_compiles_required;
	int			dongle_cooldown;
	int			start_simulation;
	bool		end_simulation;
	t_mutex		system_lock;
	t_dongle	*dongles;
	t_coder		*coders;
	char		*scheduler;

}				t_system;


#endif

