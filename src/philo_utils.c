/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontele <afontele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 14:00:40 by afontele          #+#    #+#             */
/*   Updated: 2025/08/01 15:08:37 by afontele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	msg_log(t_philo *philo, int code)
{
	pthread_mutex_lock(&philo->table->print);
	if (end_simu(philo->table) && code != DIE)
		code = -1;
	if (code == EAT)
		printf("%s%09lld %zu is eating%s\n", GREEN, get_time()
			- philo->table->start_time, philo->idx, NC);
	else if (code == SLEEP)
		printf("%s%09lld %zu is sleeping%s\n", BLUE, get_time()
			- philo->table->start_time, philo->idx, NC);
	else if (code == THINK)
		printf("%s%09lld %zu is thinking%s\n", YELLOW, get_time()
			- philo->table->start_time, philo->idx, NC);
	else if (code == DIE)
		printf("%s%09lld %zu died%s\n", RED, get_time()
			- philo->table->start_time, philo->idx, NC);
	else if (code == TAKE_FORK)
		printf("%s%09lld %zu has taken a fork%s\n", CYAN, get_time()
			- philo->table->start_time, philo->idx, NC);
	else if (code == WAIT_FORK)
		printf("%s%09lld %zu is wating for fork%s\n", YELLOW, get_time()
			- philo->table->start_time, philo->idx, NC);
	pthread_mutex_unlock(&philo->table->print);
}

int	end_simu(t_table *table)
{
	int	result;

	result = 0;
	pthread_mutex_lock(&table->m_dead);
	result = table->dead_flag;
	pthread_mutex_unlock(&table->m_dead);
	return (result);
}

void	set_end_simu(t_table *table)
{
	pthread_mutex_lock(&table->m_dead);
	table->dead_flag = 1;
	pthread_mutex_unlock(&table->m_dead);
}

void	synch_start(long long time_start)
{
	while (get_time() < time_start)
	{
		continue ;
	}
}
