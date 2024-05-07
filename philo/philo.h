/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartel <gemartel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 13:44:01 by gemartel          #+#    #+#             */
/*   Updated: 2024/03/25 16:34:29 by gemartel         ###   ########.fr       */
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
# define RED "\e[0;31m"
# define WHITE "\x1b[37;1m"
# define RESET "\x1b[0m"
# define GREEN "\e[0;32m"

/**MSG_ERROR**/
# define ERR_MALLOC "Error: Memory allocation failed with malloc.\n"

/**Msg Args Error **/
# define ERR_PHILO_NBR "Invalid philosophers number\n"
# define ERR_TIME_DIE "Invalid time to die\n"
# define ERR_TIME_EAT  "Invalid time to eat\n"
# define ERR_TIME_SLEEP "Invalid time to sleep\n"
# define ERR_TIME_EAT_PER_PHILO "Invalid number of times \
each philosopher must eat\n"
# define ERR_ARG_NBR "Error: Invalid number of arguments\n"

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
	DETACH,
	LONE_PHILO
}	t_code;

typedef struct s_table	t_table;
typedef pthread_mutex_t	t_mtx;

/**Structure**/
typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				meals_eaten;
	bool			is_full;
	long			last_meal;
	t_mtx			philo_lock;
	t_mtx			*first_fork;
	t_mtx			*second_fork;
	t_table			*table;
}					t_philo;

typedef struct s_table
{
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			philo_nbr;
	long			max_meals;
	long			start_time;
	long			threads_running_nbr;
	bool			thread_ready;
	bool			dead_flag;
	t_mtx			mtx_table;
	t_mtx			write_lock;
	t_philo			*philos;
}					t_table;

/**Initialization structures and data**/
void	init_table(t_table *table, t_philo *philos, char **argv);
void	init_forks(t_mtx *forks, int philo_nbr);
void	init_philos(t_philo *philos, t_table *table, t_mtx *forks);

/**Libft_utils**/
uint8_t	is_digit(const char *s);
uint8_t	ft_isspace(char c);
int		ft_strlen(char *str);
long	ft_atol(const char *s);

/**Check_args**/
bool	args_are_valid(int argc, char **argv);

/**Error_handler**/
void	print_error(char *s);
void	ft_putstr_fd(char *s, uint8_t fd);
void	terminate_and_cleanup(t_table *table, t_mtx *forks, t_philo *philo);

/**Mutex handler**/
void	mutex_handle(t_mtx *mutex, t_code mtxcode);

/**Thread Handler**/
void	thread_handle(t_philo *philo, t_code code);
void	wait_all_threads(t_table *table);

/**Mutex access**/
bool	get_mtxbool(t_mtx *mutex, bool *to_get);
void	set_mtxbool(t_mtx *mutex, bool *to_set, bool value);
long	get_mtxlong(t_mtx *mutex, long *to_get);
void	set_mtxlong(t_mtx *mutex, long *to_set, long value);
void	increase_long(t_mtx *mutex, long *value);

/**Time**/
long	get_time(void);
void	precise_sleep(t_table *table, long usec);
long	get_elapsed_time_ms(long timestamp_start);

/**Init_simulation**/
void	init_simulation(t_table *table, t_mtx *forks, t_philo *philos);
bool	dead_loop(t_table *table);
void	*diner_loop(void *pointer);

/**Memory Utils**/
void	free_data(t_table **table, t_philo **philos, t_mtx **forks);
void	*ft_calloc(size_t nmemb, size_t size);
bool	allocate_struct(t_table **table, t_philo **philos,
			t_mtx **forks, int phi_nbr);

/**Monitor Simulation**/
void	*monitor(void *pointer);

/**DinerRoutine**/
void	think(t_philo *philo, t_table *table, bool pre_sim);
void	eat(t_philo *philo);
void	dream(t_philo *philo, t_table *table);
void	print_message(t_table *table, char *str, int id);

void	*lone_philo(void *arg);

#endif