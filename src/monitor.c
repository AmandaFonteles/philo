/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontele <afontele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 11:39:48 by afontele          #+#    #+#             */
/*   Updated: 2025/08/04 15:10:27 by afontele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	end_sim(t_table *table)
{
	int	dead;

	pthread_mutex_lock(&table->m_dead);
	dead = table->dead_flag;
	pthread_mutex_unlock(&table->m_dead);
	return (dead);
}

static int	check_philo_dead(t_philo *philo)
{
	long long	now;

	pthread_mutex_lock(&philo->m_last_meal);
	now = get_time();
	if (now == -1)
	{
		pthread_mutex_unlock(&philo->m_last_meal);
		return (1);
	}
	if (now - philo->last_meal > (long long)philo->table->time_to_die)
	{
		pthread_mutex_unlock(&philo->m_last_meal);
		print_status(philo, "died");
		pthread_mutex_lock(&philo->table->m_dead);
		philo->table->dead_flag = 1;
		pthread_mutex_unlock(&philo->table->m_dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->m_last_meal);
	return (0);
}

static int	all_philos_full(t_table *table)
{
	size_t	i;
	int		full;

	if (table->must_eat == -1)
		return (0);
	full = 1;
	i = 0;
	while (i < table->nb_philo)
	{
		pthread_mutex_lock(&table->philos[i].m_count_meal);
		if (table->philos[i].count_meal < (size_t)table->must_eat)
			full = 0;
		pthread_mutex_unlock(&table->philos[i].m_count_meal);
		i++;
	}
	return (full);
}

void	*check_life(void *arg)
{
	t_table	*table;
	size_t	i;

	table = (t_table *)arg;
	while (get_time() < table->start_time)
		usleep(100);
	while (!end_sim(table))
	{
		i = 0;
		while (i < table->nb_philo)
		{
			if (check_philo_dead(&table->philos[i]))
				return (NULL);
			i++;
		}
		if (all_philos_full(table))
		{
			pthread_mutex_lock(&table->m_dead);
			table->dead_flag = 1;
			pthread_mutex_unlock(&table->m_dead);
			return (NULL);
		}
		usleep(500);
	}
	return (NULL);
}
