#include "../../include/philosopher.h"

static uint8_t	is_over_max_or_empty(char *content)
{
	int		len;
	long	value;

	len = ft_strlen(content);
	if (len > 10 || len == 0)
		return (1);
	value = ft_atol(content);
	if (value > INT_MAX || value < INT_MIN)
		return (1);
	return (0);
}

static uint8_t	check_content(char *content)
{
	if (is_over_max_or_empty(content))
		return (0);
	if (!is_digit(content))
			return (0);
	return (1);
}

static uint8_t	check_syntax_and_size(char **argv)
{
	if (ft_atol(argv[1]) > PHILO_MAX || ft_atol(argv[1]) <= 0 || !check_content(argv[1]))
		return (print_error(ERR_PHILO_NBR, RED, 2), 0);
	if (!check_content(argv[2]))
		return (print_error(ERR_TIME_DIE, RED, 2), 0);
	if (!check_content(argv[3]))
		return (print_error(ERR_TIME_EAT, RED, 2), 0);
	if (!check_content(argv[4]))
		return (print_error(ERR_TIME_SLEEP, RED, 2), 0);
	if (argv[5] && !check_content(argv[5]))
		return (print_error(ERR_TIME_EAT_PER_PHILO, RED, 2), 0);
	return (1);
}

uint8_t	args_are_valid(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (print_error(ERR_ARG_NBR, RED, 2), 0);
	if (!check_syntax_and_size(argv))
		return (0);
	return (1);
}