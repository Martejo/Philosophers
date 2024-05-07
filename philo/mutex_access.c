/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_access.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartel <gemartel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 09:56:35 by gemartel          #+#    #+#             */
/*   Updated: 2024/03/25 16:41:00 by gemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	get_mtxbool(t_mtx *mutex, bool *to_get)
{
	bool	ret;

	mutex_handle(mutex, LOCK);
	ret = *to_get;
	mutex_handle(mutex, UNLOCK);
	return (ret);
}

void	set_mtxbool(t_mtx *mutex, bool *to_set, bool value)
{
	mutex_handle(mutex, LOCK);
	*to_set = value;
	mutex_handle(mutex, UNLOCK);
}

long	get_mtxlong(t_mtx *mutex, long *to_get)
{
	long	ret;

	mutex_handle(mutex, LOCK);
	ret = *to_get;
	mutex_handle(mutex, UNLOCK);
	return (ret);
}

void	set_mtxlong(t_mtx *mutex, long *to_set, long value)
{
	mutex_handle(mutex, LOCK);
	*to_set = value;
	mutex_handle(mutex, UNLOCK);
}

void	increase_long(t_mtx *mutex, long *value)
{
	mutex_handle(mutex, LOCK);
	(*value)++;
	mutex_handle(mutex, UNLOCK);
}
