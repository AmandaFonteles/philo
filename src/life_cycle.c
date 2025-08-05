/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_cycle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontele <afontele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 20:01:33 by afontele          #+#    #+#             */
/*   Updated: 2025/08/05 11:18:46 by afontele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/* Manages the life cycle of each philosopher 
- Handles eating, sleeping, and thinking.
- Checks for death conditions.
- Updates meal counts and last meal times.
- Synchronizes access to shared resources using mutexes.
*/

void	init_last_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->m_last_meal);
	philo->last_meal = philo->table->start_time;
	pthread_mutex_unlock(&philo->m_last_meal);
}

void	*life_cycle(void *ph)
{
	t_philo	*philo;

	philo = (t_philo *)ph;
	init_last_meal(philo);
	while (get_time() < philo->table->start_time)
		usleep(100);
	if (philo->table->nb_philo == 1)
	{
		single_philo(philo);
		return (NULL);
	}
	if (philo->idx % 2 == 0)
		ft_usleep(philo->table->time_to_eat / 2, philo->table);
	while (!end_sim(philo->table))
	{
		if (routine(philo) != 0)
			return (NULL);
	}
	return (NULL);
}

int	start_sim(t_table *table)
{
	table->start_time = get_time() + (table->nb_philo * 2) + 100;
	if ((long long)table->start_time == -1)
	{
		printf("Error getting start time\n");
		return (1);
	}
	if (create_threads(table) != 0)
	{
		printf("Error creating threads\n");
		return (1);
	}
	join_threads(table);
	free_all(table, table->nb_philo);
	return (0);
}
