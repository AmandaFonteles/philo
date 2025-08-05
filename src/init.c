/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontele <afontele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 20:00:24 by afontele          #+#    #+#             */
/*   Updated: 2025/08/05 10:55:50 by afontele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	init_forks(pthread_mutex_t *forks, int nb_philo)
{
	int	i;

	i = 0;
	while (i < nb_philo)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&forks[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	init_mutexes(t_table *table)
{
	if (pthread_mutex_init(&table->print, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&table->m_dead, NULL) != 0)
	{
		pthread_mutex_destroy(&table->print);
		return (1);
	}
	return (0);
}

static int	init_philos(t_table *table)
{
	size_t	i;

	i = 0;
	while (i < table->nb_philo)
	{
		table->philos[i].idx = i + 1;
		table->philos[i].count_meal = 0;
		table->philos[i].last_meal = 0;
		table->philos[i].table = table;
		table->philos[i].fork_left = &table->forks[i];
		table->philos[i].fork_right = &table->forks[(i + 1) % table->nb_philo];
		if (pthread_mutex_init(&table->philos[i].m_last_meal, NULL) != 0)
			return (i);
		if (pthread_mutex_init(&table->philos[i].m_count_meal, NULL) != 0)
		{
			pthread_mutex_destroy(&table->philos[i].m_last_meal);
			return (i);
		}
		i++;
	}
	return (0);
}

int	init(t_table *table)
{
	int	err;

	table->dead_flag = 0;
	table->philos = malloc(sizeof(t_philo) * table->nb_philo);
	if (!table->philos)
		return (printf("Error allocating philosophers\n"), 1);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->nb_philo);
	if (!table->forks)
		return (free(table->philos), printf("Error allocating forks\n"), 1);
	if (init_forks(table->forks, table->nb_philo) != 0)
		return (free(table->forks), free(table->philos),
			printf("Error initializing forks\n"), 1);
	if (init_mutexes(table) != 0)
	{
		free_all(table, 0);
		return (printf("Error initializing table mutexes\n"), 1);
	}
	err = init_philos(table);
	if (err != 0)
	{
		free_all(table, err);
		return (printf("Error initializing philosophers\n"), 1);
	}
	return (0);
}
