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

/**Structure**/
typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eating;
	int				meals_eaten;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	int				num_of_philos;
	int				num_times_to_eat;
	int				*dead;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}					t_philo;
typedef struct s_table
{
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philos;
}					t_table;

typedef enum	e_mtxcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY
}	t_mtxcode;

typedef enum e_trdcode
{
	CREATE,
	JOIN,
	DETACH,
}			t_trdcode;

/**Parsing**/
uint8_t	args_are_valid(int argc, char **argv);

/**Utils_print**/
void	print_error(char *s, char *color, uint8_t fd);

/**Utils_str**/
int	ft_strlen(char *str);
uint8_t	ft_isspace(char c);
long	ft_atol(const char *s);
uint8_t	is_digit(const char *s);

/**Utils_error**/
static void	handle_mutex_error(int status, t_mtxcode mtxcode);
void	exit_error(char *strerr);

#endif