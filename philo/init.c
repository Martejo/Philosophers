/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartel <gemartel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:12:29 by gemartel          #+#    #+#             */
/*   Updated: 2024/03/25 15:53:14 by gemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philos(t_philo *philos, t_table *table, t_mtx *forks)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		philos[i].id = i + 1;
		philos[i].table = table;
		if (philos[i].id % 2 == 0)
		{
			philos[i].second_fork = &forks[i];
			philos[i].first_fork = &forks[(i + 1) % table->philo_nbr];
		}
		else
		{
			philos[i].first_fork = &forks[i];
			philos[i].second_fork = &forks[(i + 1) % table->philo_nbr];
		}
		i++;
	}
}

void	init_forks(t_mtx *forks, int philo_nbr)
{
	int	i;

	i = -1;
	while (++i < philo_nbr)
		mutex_handle(&forks[i], INIT);
}

void	init_table(t_table *table, t_philo *philos, char **argv)
{
	table->philos = philos;
	table->time_to_die = ft_atol(argv[2]);
	table->time_to_eat = ft_atol(argv[3]);
	table->time_to_sleep = ft_atol(argv[4]);
	table->philo_nbr = (int)ft_atol(argv[1]);
	table->thread_ready = false;
	if (argv[5])
		table->max_meals = (int)ft_atol(argv[5]);
	else
		table->max_meals = -1;
	mutex_handle(&table->write_lock, INIT);
	mutex_handle(&table->mtx_table, INIT);
}
