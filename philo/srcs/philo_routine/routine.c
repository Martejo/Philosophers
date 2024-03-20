/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartel <gemartel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:22:11 by gemartel          #+#    #+#             */
/*   Updated: 2024/03/20 11:51:54 by gemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosopher.h"

void	think(t_philo *philo, int pre_sim)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;
	if (pre_sim == 0)
		print_message("is thinking", philo, philo->id);
	if (philo->num_of_philos % 2 == 0)
		return ;
	t_eat = philo->time_to_eat;
	t_sleep = philo->time_to_sleep;
	t_think = (t_eat * 2) - t_sleep;
	if (t_think < 0)
		t_think = 0;
	precise_usleep(t_think * 0.42);
}

void	dream(t_philo *philo)
{
	print_message("is sleeping", philo, philo->id);
	precise_usleep(philo->time_to_sleep);
}

static void	pick_forks(t_philo *philo)
{
	// if (philo->id % 2 == 0)
	// {
	// 	pthread_mutex_lock(philo->l_fork);
	// 	print_message("has taken a fork", philo, philo->id);
	// 	pthread_mutex_lock(philo->r_fork);
	// 	print_message("has taken a fork", philo, philo->id);
	// 	return ;
	// }
	// else
	// {
	// 	pthread_mutex_lock(philo->r_fork);
	// 	print_message("has taken a fork", philo, philo->id);
	// 	pthread_mutex_lock(philo->l_fork);
	// 	print_message("has taken a fork", philo, philo->id);
	// }
	pthread_mutex_lock(philo->r_fork);
	print_message("has taken a fork", philo, philo->id);
	pthread_mutex_lock(philo->l_fork);
	print_message("has taken a fork", philo, philo->id);
}

static void	drop_forks(t_philo *philo)
{
	// if (philo->id % 2 == 0)
	// {
	// 	pthread_mutex_unlock(philo->l_fork);
	// 	pthread_mutex_unlock(philo->r_fork);
	// }
	// else
	// {
	// 	pthread_mutex_unlock(philo->r_fork);
	// 	pthread_mutex_unlock(philo->l_fork);
	// }
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

void	eat(t_philo *philo)
{
	pick_forks(philo);
	// print_message("\x1b[31;1mis eating\x1b[0m", philo, philo->id);
	philo->meals_eaten++;
	
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal = get_time();
	print_message(RED"is eating"RESET, philo, philo->id);
	if (philo->meals_eaten == philo->num_times_to_eat)
		philo->is_full = 1;
	pthread_mutex_unlock(&philo->meal_lock);
	
	precise_usleep(philo->time_to_eat);
	drop_forks(philo);
	dream(philo);
	think(philo, 0);
}