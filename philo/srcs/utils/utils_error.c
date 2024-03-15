/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartel <gemartel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:23:58 by gemartel          #+#    #+#             */
/*   Updated: 2024/03/15 16:17:15 by gemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosopher.h"

/**
 * destroy_all - Nettoie les ressources allouées, notamment en détruisant les mutex.
 * @str: Un message explicatif qui peut être utilisé pour indiquer la raison de la destruction.
 * @table: Un pointeur vers une structure représentant la table autour de laquelle les philosophes sont assis.
 * @forks: Un pointeur vers un tableau de mutex représentant les fourchettes.
 *
 * Cette fonction est appelée pour nettoyer et libérer les ressources allouées avant de terminer le programme.
 * Elle détruit les mutex utilisés pour synchroniser l'accès aux ressources partagées entre les philosophes.
 * Les mutex détruits incluent ceux utilisés pour l'écriture des logs, la vérification des repas et la détection de la mort.
 * Ensuite, la fonction itère sur le tableau des fourchettes (mutex), en détruisant chaque mutex individuellement.
 * Cela garantit que toutes les ressources de synchronisation sont correctement libérées, évitant les fuites de mémoire.
 * La fonction ne retourne pas de valeur et est généralement appelée dans des situations d'erreur ou lors de la
 * terminaison propre du programme.
 *
 * Note: La variable @str est prévue pour être utilisée dans des améliorations futures pour le logging ou la gestion d'erreurs.
 */


void	terminate_and_cleanup(char *str, t_table *table, pthread_mutex_t *forks, int nbr_thread_create)
{
	int	i;

	i = 0;
	if (str)
		print_error(str, RED, 2);
	while (i < nbr_thread_create)
	{
		handle_thread_error(pthread_join(table->philos[i].thread, NULL), JOIN);
		i++;
	}
	handle_mutex_error(pthread_mutex_destroy(&table->write_lock), DESTROY);
	handle_mutex_error(pthread_mutex_destroy(&table->meal_lock), DESTROY);
	handle_mutex_error(pthread_mutex_destroy(&table->dead_lock), DESTROY);
	while (i < table->philos[0].num_of_philos)
	{
		handle_mutex_error(pthread_mutex_destroy(&forks[i]), DESTROY);
		i++;
	}
	exit(table->error);
}

void	handle_thread_error(int status, t_status_code code)
{
	if (status == EINVAL && code == JOIN)
		print_error(JOIN_EINVAL, RED, 2);
	else if (status == ESRCH)
		print_error(JOIN_ESRCH, RED, 2);
	else if (status == EDEADLK)
		print_error(JOIN_EDEADLK, RED, 2);
	else if (status == EAGAIN)
		print_error(CREATE_EAGAIN, RED, 2);
	else if (status == EINVAL && code == CREATE)
		print_error(CREATE_EINVAL, RED, 2);
	else if (status == EPERM)
		print_error(CREATE_EPERM, RED, 2);
}


void	handle_mutex_error(int status, t_status_code code)
{
	if (0 == status)
		return ;
	if (EINVAL == status && (LOCK == code || UNLOCK == code))
		exit_error("The value specified by mutex is invalid");
	else if (EINVAL == status && INIT == code)
		exit_error("The value specified by attribute is invalid.");
	else if (EDEADLK == status)
		exit_error("A deadlock would occur if the thread "
			"blocked waiting for mutex.");
	else if (EPERM == status)
		exit_error("The current thread does not hold a lock on mutex.");
	else if (ENOMEM == status)
		exit_error("The process cannot allocate enough memory"
			" to create another mutex.");
	else if (EBUSY == status)
		exit_error("Mutex is locked");
}

void	exit_error(char *strerr)
{
	print_error(strerr, RED, 2);
	exit(EXIT_FAILURE);
}
