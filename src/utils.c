/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontele <afontele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 20:02:12 by afontele          #+#    #+#             */
/*   Updated: 2025/08/04 15:09:29 by afontele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	print_status(t_philo *philo, char *status)
{
	long long	timestamp;

	pthread_mutex_lock(&philo->table->print);
	if (end_sim(philo->table))
	{
		pthread_mutex_unlock(&philo->table->print);
		return ;
	}
	timestamp = get_timestamp(philo->table);
	if (timestamp == -1)
	{
		printf("Error getting timestamp\n");
		pthread_mutex_unlock(&philo->table->print);
		return ;
	}
	printf("%lld %zu %s\n", timestamp, philo->idx, status);
	pthread_mutex_unlock(&philo->table->print);
}

int	ft_usleep(long long time_to_wait, t_table *table)
{
	long long	stop_time;
	long long	now;

	stop_time = get_time() + time_to_wait;
	if (stop_time < 0)
		return (1);
	while (!end_sim(table))
	{
		now = get_time();
		if (now < 0)
			return (1);
		if (now >= stop_time)
			break ;
		usleep(500);
	}
	return (0);
}

long long	get_timestamp(t_table *table)
{
	long long	now;

	now = get_time();
	if (now == -1)
		return (-1);
	return (now - table->start_time);
}

long long	get_time(void)
{
	struct timeval	current_time;

	if (gettimeofday(&current_time, NULL) == -1)
		return (-1);
	return ((long long)(current_time.tv_sec * 1000)
		+ (current_time.tv_usec / 1000));
}

void	free_all(t_table *table, size_t initiated_ph)
{
	size_t	i;

	if (table->forks)
	{
		i = 0;
		while (i < table->nb_philo)
			pthread_mutex_destroy(&table->forks[i++]);
		free(table->forks);
	}
	if (table->philos)
	{
		i = 0;
		while (i < initiated_ph)
		{
			pthread_mutex_destroy(&table->philos[i].m_last_meal);
			pthread_mutex_destroy(&table->philos[i].m_count_meal);
			i++;
		}
		free(table->philos);
	}
	pthread_mutex_destroy(&table->print);
	pthread_mutex_destroy(&table->m_dead);
}
