/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontele <afontele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 19:56:46 by afontele          #+#    #+#             */
/*   Updated: 2025/08/05 10:37:24 by afontele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	main(int ac, char **av)
{
	t_table	table;

	memset(&table, 0, sizeof(t_table));
	if (parsing(ac, av, &table) != 0)
		return (1);
	if (init(&table) != 0)
		return (1);
	if (start_sim(&table) != 0)
	{
		free_all(&table, table.nb_philo);
		return (1);
	}
	return (0);
}
