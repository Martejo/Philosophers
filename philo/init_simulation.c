/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_simulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartel <gemartel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:42:28 by gemartel          #+#    #+#             */
/*   Updated: 2024/03/25 16:36:55 by gemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*lone_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_all_threads(philo->table);
	set_mtxlong(&philo->philo_lock, &philo->last_meal, get_time());
	increase_long(&philo->table->mtx_table, &philo->table->threads_running_nbr);
	print_message(philo->table, "has taken a fork", philo->id);
	while (!dead_loop(philo->table))
		precise_sleep(philo->table, 200);
	return (NULL);
}

bool	dead_loop(t_table *table)
{
	return (get_mtxbool(&table->mtx_table, &table->dead_flag));
}

static void	pre_desynchronize(t_philo *philo)
{
	if (philo->id % 2 == 0)
		precise_sleep(philo->table, 0.9 * philo->table->time_to_sleep);
}

void	*diner_loop(void *pointer)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)pointer;
	table = philo->table;
	wait_all_threads(table);
	increase_long(&table->mtx_table, &table->threads_running_nbr);
	set_mtxlong(&philo->philo_lock, &philo->last_meal, table->start_time);
	pre_desynchronize(philo);
	while (!dead_loop(table))
	{
		eat(philo);
		dream(philo, table);
		think(philo, table, false);
	}
	return (pointer);
}

void	init_simulation(t_table *table, t_mtx *forks, t_philo *philos)
{
	pthread_t	observator;
	int			i;

	i = 0;
	if (table->max_meals == 0)
		return (terminate_and_cleanup(table, forks, philos));
	else if (table->philo_nbr == 1)
		thread_handle(&table->philos[i], LONE_PHILO);
	else
	{
		while (i < table->philo_nbr)
		{
			thread_handle(&table->philos[i], CREATE);
			i++;
		}
	}
	pthread_create(&observator, NULL, monitor, table);
	set_mtxlong(&table->mtx_table, &table->start_time, get_time());
	set_mtxbool(&table->mtx_table, &table->thread_ready, true);
	pthread_join(observator, NULL);
	terminate_and_cleanup(table, forks, philos);
}
