/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartel <gemartel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 10:48:07 by gemartel          #+#    #+#             */
/*   Updated: 2024/03/25 16:39:04 by gemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	last_print(t_table *table, int id)
{
	long long	time;

	mutex_handle(&table->write_lock, LOCK);
	time = get_time() - table->start_time;
	printf(RED"%lld %d died\n"RESET, time, id);
	mutex_handle(&table->write_lock, UNLOCK);
}

bool	is_end_condition(t_table *table)
{
	t_philo	*philos;
	bool	is_dead;
	int		nb_full;
	int		i;

	i = -1;
	philos = table->philos;
	nb_full = 0;
	is_dead = false;
	while (++i < table->philo_nbr && is_dead == false)
	{
		set_mtxbool(&(philos[i].philo_lock), &is_dead, get_elapsed_time_ms
			(get_mtxlong(&(philos[i].philo_lock), &philos[i].last_meal))
			>= table->time_to_die);
		if (get_mtxbool(&(philos[i].philo_lock), &philos[i].is_full))
			nb_full++;
		if (is_dead == true || nb_full == table->philo_nbr)
		{
			set_mtxbool(&table->mtx_table, &table->dead_flag, true);
			if (is_dead)
				last_print(table, philos[i].id);
		}
	}
	return (is_dead || (nb_full == table->philo_nbr));
}

bool	all_threads_running(t_mtx *mutex, long *threads,
		long philo_nbr)
{
	bool	ret;

	ret = false;
	mutex_handle(mutex, LOCK);
	if (*threads == philo_nbr)
		ret = true;
	mutex_handle(mutex, UNLOCK);
	return (ret);
}

void	*monitor(void *pointer)
{
	t_table	*table;

	table = (t_table *)pointer;
	while (!all_threads_running(&table->mtx_table,
			&table->threads_running_nbr, table->philo_nbr))
		;
	while (!is_end_condition(table))
	{
		usleep(3000);
	}
	return (NULL);
}
