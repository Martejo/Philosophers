/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartel <gemartel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:22:11 by gemartel          #+#    #+#             */
/*   Updated: 2024/03/14 18:16:44 by gemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosopher.h"



void	think(t_philo *philo)
{
	print_message("is thinking", philo, philo->id);
}

void	dream(t_philo *philo)
{
	print_message("is sleeping", philo, philo->id);
	precise_usleep(philo->time_to_sleep);
}

// void	eat(t_philo *philo)
// {
//     pthread_mutex_t *first_fork;
//     pthread_mutex_t *second_fork;

//    // Déterminez le premier et le deuxième verrou à verrouiller
// if (philo->id == philo->num_of_philos) { // Pour le dernier philosophe
//     first_fork = philo->l_fork; // Inversement de l'ordre pour le dernier philosophe
//     second_fork = philo->r_fork;
// } else {
//     first_fork = philo->r_fork; // Ordre normal pour les autres philosophes
//     second_fork = philo->l_fork;
// }
//     // Verrouillez le premier puis le deuxième verrou
//     pthread_mutex_lock(first_fork);
//     print_message("has taken a fork", philo, philo->id);
//     pthread_mutex_lock(second_fork);
//     print_message("has taken a fork", philo, philo->id);

//     // Manger
//     philo->eating = 1;
//     pthread_mutex_lock(philo->meal_lock);
//     print_message("is eating", philo, philo->id);
//     philo->last_meal = get_time(MILLISECOND);
//     philo->meals_eaten++;
//     pthread_mutex_unlock(philo->meal_lock);
//     precise_usleep(philo->time_to_eat);
//     philo->eating = 0;

//     // Libérer les fourchettes
//     pthread_mutex_unlock(second_fork);
//     pthread_mutex_unlock(first_fork);
// }

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_message("has taken a fork", philo, philo->id);
	if (philo->num_of_philos == 1)
	{
		precise_usleep(philo->time_to_die);
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	pthread_mutex_lock(philo->l_fork);
	print_message("has taken a fork", philo, philo->id);
	philo->eating = 1;
	pthread_mutex_lock(philo->meal_lock);
	print_message("is eating", philo, philo->id);
	philo->last_meal = get_time(MILLISECOND);
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	precise_usleep(philo->time_to_eat);
	philo->eating = 0;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}