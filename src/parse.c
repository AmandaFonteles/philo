/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontele <afontele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 20:00:07 by afontele          #+#    #+#             */
/*   Updated: 2025/08/04 16:21:07 by afontele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	is_valid(const char *str)
{
	if (!str || !*str)
		return (0);
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

static long	ft_atol(const char *str)
{
	long	res;

	res = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		if (res > 2147483647)
			return (-1);
		str++;
	}
	return (res);
}

int	parsing(int ac, char **av, t_table *table)
{
	int	i;

	if (ac != 5 && ac != 6)
		return (printf("Error: Wrong number of arguments.\n"), 1);
	i = 1;
	while (i < ac)
	{
		if (!is_valid(av[i]))
			return (printf("Error: Invalid numeric argument: %s\n", av[i]), 1);
		i++;
	}
	table->nb_philo = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]);
	table->time_to_eat = ft_atol(av[3]);
	table->time_to_sleep = ft_atol(av[4]);
	if (ac == 6)
		table->must_eat = ft_atol(av[5]);
	else
		table->must_eat = -1;
	if (table->nb_philo <= 0 || table->time_to_die < 0
		|| table->time_to_eat < 0 || table->time_to_sleep < 0
		|| (ac == 6 && table->must_eat <= 0))
		return (printf("Error: Invalid argument values.\n"), 1);
	return (0);
}
