/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartel <gemartel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 13:56:03 by gemartel          #+#    #+#             */
/*   Updated: 2024/03/20 14:33:57 by gemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	is_over_max_or_empty(char *content)
{
	int		len;
	long	value;

	len = ft_strlen(content);
	if (len > 10 || len == 0)
		return (true);
	value = ft_atol(content);
	if (value > INT_MAX || value < INT_MIN)
		return (true);
	return (false);
}

static bool	check_content(char *content)
{
	if (is_over_max_or_empty(content))
		return (false);
	if (!is_digit(content))
			return (false);
	return (true);
}

static bool	check_syntax_and_size(char **argv)
{
	if (ft_atol(argv[1]) > PHILO_MAX || ft_atol(argv[1]) <= 0 || !check_content(argv[1]))
		return (print_error(ERR_PHILO_NBR), false);
	if (!check_content(argv[2]))
		return (print_error(ERR_TIME_DIE), false);
	if (!check_content(argv[3]))
		return (print_error(ERR_TIME_EAT), false);
	if (!check_content(argv[4]))
		return (print_error(ERR_TIME_SLEEP), false);
	if (argv[5] && !check_content(argv[5]))
		return (print_error(ERR_TIME_EAT_PER_PHILO), false);
	return (true);
}

bool	args_are_valid(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (print_error(ERR_ARG_NBR), false);
	if (!check_syntax_and_size(argv))
		return (false);
	return (true);
}