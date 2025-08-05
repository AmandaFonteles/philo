/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontele <afontele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 19:56:24 by afontele          #+#    #+#             */
/*   Updated: 2025/08/05 11:35:22 by afontele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

/****************************** STRUCTS *********************************** */
typedef struct s_table	t_table;

typedef struct s_philo
{
	size_t				idx;
	size_t				count_meal;
	pthread_t			philo_thread;
	pthread_mutex_t		*fork_left;
	pthread_mutex_t		*fork_right;
	pthread_mutex_t		m_last_meal;
	pthread_mutex_t		m_count_meal;
	long long			last_meal;
	t_table				*table;
}	t_philo;

struct s_table
{
	int					dead_flag;
	size_t				nb_philo;
	long long			time_to_die;
	long long			time_to_eat;
	long long			time_to_sleep;
	long long			start_time;
	long long			must_eat;
	t_philo				*philos;
	pthread_t			monitor;
	pthread_mutex_t		*forks;
	pthread_mutex_t		m_dead;
	pthread_mutex_t		print;
};

/****************************** FUNCTIONS *********************************/
/* PARSE */
int			parsing(int ac, char **av, t_table *table);

/* INIT */
int			init(t_table *table);

/* LIFE CYCLE */
void		init_last_meal(t_philo *philo);
void		*life_cycle(void *ph);
int			start_sim(t_table *table);

/* THREADS */
int			create_threads(t_table *table);
void		join_threads(t_table *table);

/* MONITOR */
int			end_sim(t_table *table);
void		*check_life(void *arg);

/* ROUTINE */
void		*single_philo(t_philo *philo);
void		*routine(t_philo *philo);
int			eat_philo(t_philo *philo);

/* ACTIONS */
int			sleep_philo(t_philo *philo);
int			think_philo(t_philo *philo);

/* UTILS */
void		print_status(t_philo *philo, char *status);
int			ft_usleep(long long time_to_wait, t_table *table);
long long	get_timestamp(t_table *table);
long long	get_time(void);
void		free_all(t_table *table, size_t initiated_ph);

#endif
