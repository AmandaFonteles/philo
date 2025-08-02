/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontele <afontele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 13:12:33 by afontele          #+#    #+#             */
/*   Updated: 2025/08/02 15:30:16 by afontele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	free_philo(t_table *table)
{
	size_t	i;
	
	i = 0;
	if (table->forks)
	{
		while (i < table->nb_philo)
		{
			pthread_mutex_destroy(&table->forks[i]);
			i++;
		}
		free(table->forks);
	}

	if (table->philos)
	{
		i = 0;
		while (i < table->nb_philo)
		{
			pthread_mutex_destroy(&table->philos[i].m_last_meal);
			pthread_mutex_destroy(&table->philos[i].m_count_meal);
			i++;
		}
		free(table->philos);
	}
}


void	ft_free(t_table *table)
{
	size_t	i;

	i = 0;

	while (i < table->nb_philo)
	{
		pthread_mutex_destroy(&table->forks[i]);
		pthread_mutex_destroy(&table->philos[i].m_last_meal);
		pthread_mutex_destroy(&table->philos[i].m_count_meal);
		i++;
	}
	free(table->forks);
	free(table->philos);
	pthread_mutex_destroy(&table->m_dead);
	pthread_mutex_destroy(&table->print);
}
//call free when the simulation is over
//to free all the alloc mem and destroy all the mutex
int	msg_err(int key_error)
{
	if (key_error == ARG_ERR)
		printf("\033[1;31mError, please enter valid arguments.\033[0m\n\n"
			"  => \033[1;34m./philo <time_to_die> <time_to_eat> <time_to_sleep>"
			"[number_of_time_must_eat]\033[0m\n\n");
	else if (key_error == SIMULATION_ERR)
		printf("\033[1;31mError with simulation !\033[0m\n\n");
	return (EXIT_FAILURE);
}

int	safe_thread(pthread_t *thread, void *(*func)(void *), void *arg)
{
	if (pthread_create(thread, NULL, func, arg))
		return (1);
	return (0);
}

int	join_philos(t_table *table, size_t count)
{
	size_t i = 0;
	while (i < count)
	{
		pthread_join(table->philos[i].philo_thread, NULL);
		i++;
	}
	return (0);
}
