/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontele <afontele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 20:00:46 by afontele          #+#    #+#             */
/*   Updated: 2025/08/04 15:08:02 by afontele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	join_early(t_table *table, size_t count)
{
	size_t	i;

	i = 0;
	pthread_mutex_lock(&table->m_dead);
	table->dead_flag = 1;
	pthread_mutex_unlock(&table->m_dead);
	while (i < count)
	{
		pthread_join(table->philos[i].philo_thread, NULL);
		i++;
	}
	return (0);
}

int	create_threads(t_table *table)
{
	size_t	i;

	i = 0;
	while (i < table->nb_philo)
	{
		if (pthread_create(&table->philos[i].philo_thread,
				NULL, &life_cycle, &table->philos[i]) != 0)
		{
			join_early(table, i);
			return (1);
		}
		i++;
	}
	if (pthread_create(&table->monitor, NULL, &check_life, table) != 0)
	{
		join_early(table, table->nb_philo);
		return (1);
	}
	return (0);
}

void	join_threads(t_table *table)
{
	size_t	i;

	i = 0;
	while (i < table->nb_philo)
	{
		pthread_join(table->philos[i].philo_thread, NULL);
		i++;
	}
	pthread_join(table->monitor, NULL);
}
