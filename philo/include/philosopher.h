#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H





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
long 	get_time();
void	precise_usleep(long  usec);

/**Threads_handler**/
void	*monitor(void *pointer);
uint8_t	thread_create(t_table *table, pthread_mutex_t *forks);
void	print_message(char *str, t_philo *philo, int id);
int	dead_loop(t_philo *philo);

/**Philo_routine**/
void	think(t_philo *philo, int pre_sim);
void	dream(t_philo *philo);
void	eat(t_philo *philo);


#endif