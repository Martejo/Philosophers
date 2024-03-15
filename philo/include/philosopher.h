#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

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

# define PHILO_MAX 300

/**COLOR**/
# define RED     "\x1b[31;1m"
# define RESET   "\x1b[0m"

/**MSG_ERROR**/
# define ERR_PHILO_NBR "Invalid philosophers number\n"
# define ERR_TIME_DIE "Invalid time to die\n"
# define ERR_TIME_EAT  "Invalid time to eat\n"
# define ERR_TIME_SLEEP "Invalid time to sleep\n"
# define ERR_TIME_EAT_PER_PHILO  "Invalid number of times each philosopher must eat\n"
# define ERR_ARG_NBR "Error: Invalid number of arguments\n"
# define JOIN_EINVAL "The specified thread is not reachable or another thread is already waiting for it to finish."
# define JOIN_ESRCH "No thread with the specified ID could be found."
# define JOIN_EDEADLK "A deadlock has been detected or the thread is trying to join itself."
# define CREATE_EAGAIN "The resources required to create a new thread are not available, or the system has reached its thread limit."
# define CREATE_EINVAL "The specified attributes are invalid."
# define CREATE_EPERM "Permissions are not sufficient to set the scheduling policy or the scheduling parameters specified in the attributes.\n"

/**Structure**/

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eating;
	int				meals_eaten;
	long			last_meal;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			start_time;
	int				num_of_philos;
	int				num_times_to_eat;
	int				*error;
	int				*thread_ready;
	int				*dead;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}					t_philo;

typedef struct s_table
{
	int				error;
	int				thread_ready;
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philos;
}					t_table;

typedef enum e_statut_code
{
	JOIN,
	CREATE,
	INIT,
	LOCK,
	UNLOCK,
	DESTROY
}	t_status_code;

typedef enum e_time_code
{
	SECONDS,
	MILLISECOND,
	MICROSECOND,
}		t_time_code;

/**Parsing**/
uint8_t	args_are_valid(int argc, char **argv);

/**Init**/
void	init_input(t_philo *philo, char **argv);
void	init_philos(t_philo *philos, t_table *table, pthread_mutex_t *forks, char **argv, int philo_nbr);
void	init_forks(pthread_mutex_t *forks, int philo_num);
void	init_launcher(t_table *table, t_philo *philos);

/**Utils_print**/
void	print_error(char *s, char *color, uint8_t fd);

/**Utils_str**/
int	ft_strlen(char *str);
uint8_t	ft_isspace(char c);
long	ft_atol(const char *s);
uint8_t	is_digit(const char *s);

/**Utils_error**/
void	handle_mutex_error(int status, t_status_code code);
void	exit_error(char *strerr);
void	handle_thread_error(int status, t_status_code code);
void	terminate_and_cleanup(char *str, t_table *table, pthread_mutex_t *forks, int nbr_thread_create);


/**Utils_time**/
long	get_time(int time_status);
void	precise_usleep(long usec);

/**Threads_handler**/
void	*monitor(void *pointer);
uint8_t	thread_create(t_table *table, pthread_mutex_t *forks);
void	print_message(char *str, t_philo *philo, int id);
int	dead_loop(t_philo *philo);

/**Philo_routine**/
void	think(t_philo *philo);
void	dream(t_philo *philo);
void	eat(t_philo *philo);


#endif