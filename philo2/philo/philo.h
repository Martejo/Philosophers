/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartel <gemartel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 13:44:01 by gemartel          #+#    #+#             */
/*   Updated: 2024/03/20 16:25:41 by gemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>
# include <stdint.h>
# include <limits.h>
# include <errno.h>
# include <stdbool.h>

/**COLOR**/
# define RED     "\x1b[31;1m"
#define WHITE    "\x1b[37;1m"
# define RESET   "\x1b[0m"
/****/

/**MSG_ERROR**/
# define ERR_MALLOC "Error: Memory allocation failed with malloc. The requested memory could not be allocated.\n"

/**Msg Args Error **/
# define ERR_PHILO_NBR "Invalid philosophers number\n"
# define ERR_TIME_DIE "Invalid time to die\n"
# define ERR_TIME_EAT  "Invalid time to eat\n"
# define ERR_TIME_SLEEP "Invalid time to sleep\n"
# define ERR_TIME_EAT_PER_PHILO  "Invalid number of times each philosopher must eat\n"
# define ERR_ARG_NBR "Error: Invalid number of arguments\n"

/**Msg Thread Error**/
# define CREATE_EAGAIN "The resources required to create a new thread are not available, or the system has reached its thread limit."
# define CREATE_EINVAL "The specified attributes are invalid."
# define CREATE_EPERM "Permissions are not sufficient to set the scheduling policy or the scheduling parameters specified in the attributes.\n"
# define JOIN_EINVAL "The specified thread is not reachable or another thread is already waiting for it to finish."
# define JOIN_ESRCH "No thread with the specified ID could be found."
# define JOIN_EDEADLK "A deadlock has been detected or the thread is trying to join itself."

/**Msg Mutex Error**/
# define MTX_EINVAL_INIT "The value specified by attribute is invalid.\n"
# define MTX_EINVAL_LOCK "The value specified by mutex is invalid\n"
# define MTX_EDEADLK "A deadlock would occur if the thread blocked waiting for mutex.\n"
# define MTX_EPERM "The current thread does not hold a lock on mutex.\n"
# define MTX_ENOMEM "The process cannot allocate enough memory to create another mutex.\n"
# define MTX_EBUSY "Mutex is locked\n"

/**Max philo**/
# define PHILO_MAX 200

/**define status code to manage mutex and thread errors**/
typedef enum e_code
{
	JOIN,
	CREATE,
	INIT,
	LOCK,
	UNLOCK,
	DESTROY,
	DETACH
}	t_code;

typedef struct s_table	t_table;


/**Structure**/

typedef struct e_mtx
{
	pthread_mutex_t	mutex;
	bool	is_lock;
	bool	initialized;
}	t_mtx;

typedef struct e_thread
{
	pthread_t		thread;
	bool			initialized;
}	t_thread;

typedef struct s_philo
{
	t_thread		thread;
	int				id;
	int				meals_eaten;
	bool			is_full;
	long 			last_meal;
	int				*dead;
	t_table			*table;
	t_mtx			*first_fork;
	t_mtx			*second_fork;
	t_mtx			philo_lock;
}					t_philo;

typedef struct s_table
{
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			philo_nbr;
	long			max_meals;
	long			start_time;
	bool			thread_ready;
	int				dead_flag;
	long			start_time;
	t_mtx			dead_lock;
	t_mtx			write_lock;
	t_philo			*philos;
}					t_table;

/**Initialization structures and data**/
bool	init_table(t_table *table, t_philo *philos, char **argv);
bool	init_forks(t_mtx *forks, int philo_nbr);
void	init_philos(t_philo *philos, t_table *table, t_mtx *forks);

/**Libft_utils**/
uint8_t	is_digit(const char *s);
uint8_t	ft_isspace(char c);
int		ft_strlen(char *str);
long	ft_atol(const char *s);
/****/

/**Check_args**/
bool	args_are_valid(int argc, char **argv);

/**Error_handler**/
void	print_error(char *s);

/**Mutex handler**/
bool	safe_mutex_handle(t_mtx *mutex, t_code mtxcode);

/**Thread Handler**/
bool	safe_thread_handle(t_philo *philo, t_code code);








void	free_data(t_table **table, t_philo **philos, t_mtx **forks);


#endif