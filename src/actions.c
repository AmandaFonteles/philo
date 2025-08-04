/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontele <afontele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 15:20:00 by afontele          #+#    #+#             */
/*   Updated: 2025/08/04 16:21:06 by afontele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	sleep_philo(t_philo *philo)
{
	if (end_sim(philo->table))
		return (1);
	print_status(philo, "is sleeping");
	ft_usleep(philo->table->time_to_sleep, philo->table);
	return (0);
}

int	think_philo(t_philo *philo)
{
	if (end_sim(philo->table))
		return (1);
	print_status(philo, "is thinking");
	ft_usleep(1, philo->table);
	return (0);
}
