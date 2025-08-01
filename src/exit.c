/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontele <afontele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 13:12:33 by afontele          #+#    #+#             */
/*   Updated: 2025/08/01 17:19:13 by afontele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	free_philo(t_table *table)
{
	size_t	i;

	i = 0;
	free(table->philos);
	while (i < table->nb_philo)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	free(table->forks);
}

void	ft_free(t_table *table)
{
	size_t	i;

	i = 0;

	while (i < table->nb_philo)
	{
		pthread_mutex_destroy(&table->forks[i]);
		pthread_mutex_destroy(&table->philos[i].m_count_meal);
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

