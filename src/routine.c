/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontele <afontele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 01:56:02 by afontele          #+#    #+#             */
/*   Updated: 2025/08/04 18:47:41 by afontele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*routine(t_philo *philo)
{
	while (!end_sim(philo->table))
	{
		if (eat_philo(philo) != 0)
			return (NULL);
		if (end_sim(philo->table))
			break ;
		if (sleep_philo(philo) != 0)
			return (NULL);
		if (end_sim(philo->table))
			break ;
		if (think_philo(philo) != 0)
			return (NULL);
	}
	return (NULL);
}

static void	take_forks(t_philo *philo)
{
	if (philo->idx % 2 == 0)
	{
		pthread_mutex_lock(philo->fork_right);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->fork_left);
		print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->fork_left);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->fork_right);
		print_status(philo, "has taken a fork");
	}
}

static void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
}

void	*single_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_left);
	print_status(philo, "has taken a fork");
	usleep(philo->table->time_to_die * 1000);
	pthread_mutex_unlock(philo->fork_left);
	print_status(philo, "died");
	pthread_mutex_lock(&philo->table->m_dead);
	philo->table->dead_flag = 1;
	pthread_mutex_unlock(&philo->table->m_dead);
	return (NULL);
}

int	eat_philo(t_philo *philo)
{
	if (end_sim(philo->table))
		return (1);
	take_forks(philo);
	pthread_mutex_lock(&philo->m_last_meal);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->m_last_meal);
	print_status(philo, "is eating");
	ft_usleep(philo->table->time_to_eat, philo->table);
	pthread_mutex_lock(&philo->m_count_meal);
	philo->count_meal++;
	pthread_mutex_unlock(&philo->m_count_meal);
	release_forks(philo);
	return (0);
}
