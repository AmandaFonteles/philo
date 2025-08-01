/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontele <afontele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 13:13:01 by afontele          #+#    #+#             */
/*   Updated: 2025/08/01 14:00:35 by afontele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	ft_wait(long long time_to_wait, t_table *table)
{
	long long	time;

	time = get_time() + time_to_wait;
	while (!end_simu(table) && get_time() < time)
		usleep(500);
}

/**
 * for getting current time in ms
 */
long long	get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((long long)(current_time.tv_sec * 1000LL) + (current_time.tv_usec
			/ 1000));
}

