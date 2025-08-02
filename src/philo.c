/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontele <afontele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 13:53:16 by afontele          #+#    #+#             */
/*   Updated: 2025/08/02 15:29:08 by afontele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	launch_simulation(t_table *table)
{
	size_t	i;

	i = 0;
	while (i < table->nb_philo)
	{
		if (safe_thread(&table->philos[i].philo_thread, routine, &table->philos[i]))
		{
			join_philos(table, i);
			return (1);
		}
		i++;
	}
	if (safe_thread(&table->monitor, handle_life, table))
	{
		join_philos(table, table->nb_philo);
		return (1);
	}
	join_philos(table, table->nb_philo);
	pthread_join(table->monitor, NULL);

	return (0);
}

//To avoid race conditions at the start of the simulation,
//we wait a little bit before starting the simulation,
//so that all philosophers are ready to start at the same time.
int	main(int ac, char **av)
{
	t_table	table;

	if (parsing(ac, av, &table))
		return (msg_err(ARG_ERR)); //change the errors
	table.start_time = get_time() + (table.nb_philo * 20);
	if (launch_simulation(&table))
		return (msg_err(SIMULATION_ERR)); //change the errors
	ft_free(&table);
	return (0);
}
