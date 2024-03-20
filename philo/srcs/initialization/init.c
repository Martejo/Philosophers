#include "../../include/philosopher.h"

void	init_input(t_philo *philo, char **argv)
{
	philo->time_to_die = ft_atol(argv[2]);
	philo->time_to_eat = ft_atol(argv[3]);
	philo->time_to_sleep = ft_atol(argv[4]);
	philo->num_of_philos = (int)ft_atol(argv[1]);
	if (argv[5])
		philo->num_times_to_eat = (int)ft_atol(argv[5]);
	else
		philo->num_times_to_eat = -1;
}

void	init_philos(t_philo *philos, t_table *table, pthread_mutex_t *forks, char **argv, int philo_nbr)
{
	int	i;
	
	i = 0;
	while (i < philo_nbr)
	{
		handle_mutex_error(pthread_mutex_init(&philos[i].meal_lock, NULL), INIT);
		init_input(&philos[i], argv);
		philos[i].id = i + 1;
		philos[i].table = table;
		philos[i].meals_eaten = 0;
		//philos[i].start_time = &table->start_time;
		philos[i].last_meal = get_time(MILLISECOND);
		philos[i].write_lock = &table->write_lock;
		philos[i].dead_lock = &table->dead_lock;
		// philos[i].meal_lock = &table->meal_lock;
		philos[i].dead = &table->dead_flag;
		philos[i].error = &table->error;
		philos[i].thread_ready = &table->thread_ready;
		// philos[i].l_fork = &forks[i];
		// philos[i].r_fork = &forks[(i + 1) % philo_nbr];
		
		// if (philo_nbr % 2 == 0)
		// {
			if (philos[i].id % 2 == 0) 
			{ // ID pair
				philos[i].l_fork = &forks[i];
				philos[i].r_fork = &forks[(i + 1) % philo_nbr];
			} 	
			else 
			{
				philos[i].r_fork = &forks[i];
				philos[i].l_fork = &forks[(i + 1) % philo_nbr];
			}
		//}
		// else
		// {
		// 	if (philos[i].id == philo_nbr)
		// 	{
		// 		philos[i].l_fork = &forks[0];
		// 		philos[i].r_fork = &forks[i];
		// 	}
		// 	else if (philos[i].id % 2 == 0) 
		// 	{ // ID pair
		// 		philos[i].l_fork = &forks[i];
		// 		philos[i].r_fork = &forks[(i + 1) % philo_nbr];
		// 	} 	
		// 	else
		// 	{
		// 		philos[i].r_fork = &forks[i];
		// 		philos[i].l_fork = &forks[(i + 1) % philo_nbr];
		// 	}
		// }
		i++;
	}
}

void	init_forks(pthread_mutex_t *forks, int philo_num)
{
	int	i;

	i = 0;
	while (i < philo_num)
	{
		handle_mutex_error(pthread_mutex_init(&forks[i], NULL), INIT);
		i++;
	}
}

void init_launcher(t_table *table, t_philo *philos)
{
	table->dead_flag = 0;
	table->philos	= philos;
	table->error	= 0;
	table->thread_ready = 0;
	handle_mutex_error(pthread_mutex_init(&table->write_lock, NULL), INIT);
	handle_mutex_error(pthread_mutex_init(&table->dead_lock, NULL), INIT);
}