/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartel <gemartel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:02:19 by gemartel          #+#    #+#             */
/*   Updated: 2024/03/22 14:50:45 by gemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	terminate_and_cleanup(t_table *table, t_mtx *forks, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < table->philo_nbr)
	{
		thread_handle(&philo[i], JOIN);
		mutex_handle(&philo[i].philo_lock, DESTROY);
	}
	mutex_handle(&table->write_lock, DESTROY);
	mutex_handle(&table->mtx_table, DESTROY);
	i = -1;
	while (++i < table->philo_nbr)
		mutex_handle(&forks[i], DESTROY);
	free_data(&table, &philo, &forks);
}

void	ft_putstr_fd(char *s, uint8_t fd)
{
	if (s)
		write(fd, s, ft_strlen(s));
}

void	print_error(char *s)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd(RESET, 2);
}
