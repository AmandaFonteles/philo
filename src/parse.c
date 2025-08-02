/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontele <afontele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 13:59:57 by afontele          #+#    #+#             */
/*   Updated: 2025/08/02 16:43:27 by afontele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
//mudar atoi p atoll
static long	atoi_plus(const char *str, int *error)
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
		result = result * 10 + (str[i] - '0');
		i++;
		if ((result > INT_MAX))
			*error = 1;
	}
	return (result);
}

static int	init_mutex(t_table *table)
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
		{
			table->nb_philo = i;
			return (1);
		}
		if (pthread_mutex_init(&table->philos[i].m_count_meal, NULL))
		{
			table->nb_philo = i;
			return (1);
		}
		i++;
	}
	return (0);
}
//This function assigns the left and right forks to each philosopher.
//The left fork to odd philo and right fork to even philo.
//This is to avoid deadlocks and ensure that each philosopher
//has access to both forks.
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

//Philos starts with 1 and forks starts with 0
//If a mutex fails to initialize, we free save i in nb_philo
//So we have i philos that are initialized
// and can call free_philo to free them
static int	init_philos(t_table *table)
{
	size_t	i;

	i = 0;
	table->philos = malloc(table->nb_philo * sizeof(t_philo));
	table->forks = malloc(table->nb_philo * sizeof(pthread_mutex_t));
	if (!table->philos || !table->forks)
		return (1);
	memset(table->philos, 0, table->nb_philo * sizeof(t_philo));
	while (i < table->nb_philo)
	{
		if (pthread_mutex_init(&table->forks[i], NULL))
		{
			table->nb_philo = i;
			return (1);
		}
		table->philos[i].idx = i + 1;
		table->philos[i].table = table;
		table->philos[i].count_meal = 0;
		table->philos[i].last_meal = table->start_time;
		assign_forks(&table->philos[i], i);
		i++;
	}
	return (0);
}
// This function parses the arguments, initializes the table and philosophers,
// and returns 0 if successful, or 1 if there was an error.
int	parsing(int argc, char **argv, t_table *table)
{
	int	error;

	error = 0;
	if (!(argc == 5 || argc == 6))
		return (1);
	memset(table, 0, sizeof(t_table));
	table->nb_philo = atoi_plus(argv[1], &error);
	table->time_to_die = atoi_plus(argv[2], &error);
	table->time_to_eat = atoi_plus(argv[3], &error);
	table->time_to_sleep = atoi_plus(argv[4], &error);
	table->dead_flag = 0;
	if (argc == 6)
		table->must_eat = atoi_plus(argv[5], &error);
	else
		table->must_eat = 0;
	if (error)
		return (1);
	if (init_philos(table))
		return (free_philo(table), 1);
	if (init_mutex(table))
		return (free_philo(table), 1);
	return (error);
}
