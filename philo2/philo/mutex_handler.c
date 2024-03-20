/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartel <gemartel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:23:53 by gemartel          #+#    #+#             */
/*   Updated: 2024/03/20 16:26:01 by gemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	handle_mutex_error(int mtx_err, t_code status)
{
	if (0 == mtx_err)
		return (true);
	if (EINVAL == mtx_err && (LOCK == status || UNLOCK == status))
		return (print_error(MTX_EINVAL_LOCK), false);
	else if (EINVAL == mtx_err && INIT == status)
		return (print_error(MTX_EINVAL_INIT), false);
	else if (EDEADLK == mtx_err)
		return (print_error(MTX_EDEADLK), false);
	else if (EPERM == mtx_err)
		return (print_error(MTX_EPERM), false);
	else if (ENOMEM == mtx_err)
		return (print_error(MTX_ENOMEM), false);
	else if (EBUSY == mtx_err)
		return (print_error(MTX_EBUSY), false);
	return (true);
}

bool	safe_mutex_handle(t_mtx *mutex, t_code mtxcode)
{
	if (LOCK == mtxcode)
	{
		mutex->is_lock = 1;
		return(handle_mutex_error(pthread_mutex_lock(mutex), mtxcode));
	}
	else if (UNLOCK == mtxcode)
		return (handle_mutex_error(pthread_mutex_unlock(mutex), mtxcode));
	else if (INIT == mtxcode && !mutex->initialized)
	{
		if (!handle_mutex_error(pthread_mutex_init(mutex, NULL), mtxcode))
			return (false);
		mutex->initialized = true;
	}
	else if (DESTROY == mtxcode && mutex->initialized)
	{
		handle_mutex_error(pthread_mutex_destroy(mutex), mtxcode);
		mutex->initialized = false;
	}
	return (true);
}