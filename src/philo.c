/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontele <afontele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 13:53:16 by afontele          #+#    #+#             */
/*   Updated: 2025/08/01 16:43:08 by afontele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	launch_simulation(t_table *table)
{
	size_t	i;

	i = 0;
	while (i < table->nb_philo)
	{
		if (pthread_create(&table->philos[i].philo_thread, NULL, &routine,
				&table->philos[i]))
			return (1);
		i++;
	}
	if (pthread_create(&table->monitor, NULL, &handle_life, table))
		return (1);
	i = 0;
	while (i < table->nb_philo)
	{
		if (pthread_join(table->philos[i].philo_thread, NULL))
			return (1);
		i++;
	}
	if (pthread_join(table->monitor, NULL))
		return (1);
	return (0);
}

//To avoid race conditions at the start of the simulation,
//we wait a little bit before starting the simulation,
//so that all philosophers are ready to start at the same time.
int	main(int ac, char **av)
{
	t_table	table;

	if (ft_parse(ac, av, &table))
		return (msg_err(ARG_ERR)); //change the errors
	table.start_time = get_time() + (table.nb_philo * 20);
	if (launch_simulation(&table))
		return (msg_err(SIMULATION_ERR)); //change the errors
	ft_free(&table);
	return (0);
}
