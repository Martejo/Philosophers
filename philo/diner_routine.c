/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diner_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartel <gemartel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 10:09:06 by gemartel          #+#    #+#             */
/*   Updated: 2024/03/25 16:00:42 by gemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(t_table *table, char *str, int id)
{
	long	time;

	mutex_handle(&table->write_lock, LOCK);
	time = get_time() - table->start_time;
	if (!dead_loop(table))
		printf(GREEN"%ld %d %s\n"RESET, time, id, str);
	mutex_handle(&table->write_lock, UNLOCK);
}

void	think(t_philo *philo, t_table *table, bool pre_sim)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;

	if (pre_sim == false)
		print_message(table, "is thinking", philo->id);
	if (table->philo_nbr % 2 == 0)
		return ;
	t_eat = table->time_to_eat;
	t_sleep = table->time_to_sleep;
	t_think = (t_eat * 2) - t_sleep;
	if (t_think < 0)
		t_think = 0;
	precise_sleep(table, t_think * 0.10);
}

void	dream(t_philo *philo, t_table *table)
{
	print_message(table, "is sleeping", philo->id);
	precise_sleep(table, table->time_to_sleep);
}

void	eat(t_philo *philo)
{
	mutex_handle(philo->first_fork, LOCK);
	mutex_handle(philo->second_fork, LOCK);
	print_message(philo->table, "has taken a fork", philo->id);
	print_message(philo->table, "has taken a fork", philo->id);
	philo->meals_eaten++;
	set_mtxlong(&philo->philo_lock, &philo->last_meal, get_time());
	print_message(philo->table, "is eating", philo->id);
	precise_sleep(philo->table, philo->table->time_to_eat);
	if (philo->meals_eaten == philo->table->max_meals)
		set_mtxbool(&philo->philo_lock, &philo->is_full, true);
	mutex_handle(philo->first_fork, UNLOCK);
	mutex_handle(philo->second_fork, UNLOCK);
}
