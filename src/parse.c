/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontele <afontele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 13:59:57 by afontele          #+#    #+#             */
/*   Updated: 2025/08/01 16:34:42 by afontele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static long	ft_atoi_boost(const char *str, int *error)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			*error = 1;
	if (!(str[i] >= '0' && str[i] <= '9'))
		*error = 1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - 48);
		i++;
		if ((result > INT_MAX))
			*error = 1;
	}
	return (result);
}

static int	ft_init_mutex(t_table *table)
{
	size_t i;

	i = 0;
	if (pthread_mutex_init(&table->print, NULL))
		return (1);
	if (pthread_mutex_init(&table->m_dead, NULL))
		return (1);
	while (i < table->nb_philo)
	{
		if (pthread_mutex_init(&table->philos[i].m_last_meal, NULL))
			return (1);
		if (pthread_mutex_init(&table->philos[i].m_count_meal, NULL))
			return (1);
		i++;
	}
	return (0);
}

static void	assign_forks(t_philo *philo, size_t i)
{
	if (philo->idx % 2)
	{
		philo->fork_left = &philo->table->forks[i];
		philo->fork_right = &philo->table->forks[(i + 1)
			% philo->table->nb_philo];
	}
	else
	{
		philo->fork_right = &philo->table->forks[i];
		philo->fork_left = &philo->table->forks[(i + 1)
			% philo->table->nb_philo];
	}
}

/**
 * malloc the table of philos and the table of mutex forks
 * assign the mutex (fork) of the table left and right to each philosopher
 * init the log mutex pointeur to each philo
 * assign all other relevant information
 */
static int	ft_init_philo(t_table *table)
{
	size_t	i;

	table->philos = malloc(table->nb_philo * sizeof(t_philo));
	table->forks = malloc(table->nb_philo * sizeof(pthread_mutex_t));
	if (!table->philos || !table->forks)
		return (1);
	i = 0;
	memset(table->philos, 0, table->nb_philo * sizeof(t_philo));
	while (i < table->nb_philo)
	{
		if (pthread_mutex_init(&table->forks[i], NULL))
			return (1);
		table->philos[i].idx = i + 1;
		table->philos[i].table = table;
		table->philos[i].count_meal = 0;
		assign_forks(&table->philos[i], i);
		i++;
	}
	return (0);
}

int	ft_parse(int argc, char **argv, t_table *table)
{
	int	error;

	error = 0;
	if (!(argc == 5 || argc == 6))
		return (1);
	table->nb_philo = ft_atoi_boost(argv[1], &error);
	table->time_to_die = ft_atoi_boost(argv[2], &error);
	table->time_to_eat = ft_atoi_boost(argv[3], &error);
	table->time_to_sleep = ft_atoi_boost(argv[4], &error);
	table->dead_flag = 0;
	if (argc == 6)
	{
		table->must_eat = ft_atoi_boost(argv[5], &error);
		if (!table->must_eat)
			return (1);
	}
	else
		table->must_eat = 0;
	if (error)
		return (1);
	error = ft_init_philo(table);
	if (ft_init_mutex(table))
		return (free_philo(table), 1);
	return (error);
}
