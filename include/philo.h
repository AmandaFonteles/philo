/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontele <afontele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 13:11:01 by afontele          #+#    #+#             */
/*   Updated: 2025/08/01 16:16:29 by afontele         ###   ########.fr       */
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

# define GREEN "\033[0;32m"
# define BLUE "\033[0;36m"
# define YELLOW "\033[0;33m"
# define RED "\033[1;31m"
# define CYAN "\033[0;35m"
# define FLASH "\033[1;93m"
# define NC "\033[0m"

# define ARG_ERR 13 
# define SIMULATION_ERR 14

/****************************** STRUCTS *********************************** */
typedef struct s_table t_table;

//There one t_philo for each philosopher
typedef struct s_philo
{
    size_t idx;
    size_t count_meal;
    pthread_t philo_thread;
    pthread_mutex_t *fork_left;
    pthread_mutex_t *fork_right;
    pthread_mutex_t m_last_meal;
    pthread_mutex_t m_count_meal;
    long long last_meal;
    t_table *table;
}   t_philo;

struct s_table
{
    int dead_flag;
    size_t nb_philo; //total nb of philos
    size_t time_to_die;
    size_t time_to_eat;
    size_t time_to_sleep;
    size_t start_time;
    size_t must_eat; //total times a philo must eat before simulation end
    t_philo *philos; //array of philosophers
    pthread_t monitor; //Thread monitors philos, check death and meal counts.
    pthread_mutex_t *forks; //array_of_forks
    pthread_mutex_t m_dead;
    pthread_mutex_t print; //mutex to sync print
};

/****************************** ENUM **************************************/
enum
{
    EAT,
    SLEEP,
    THINK,
    DIE,
    TAKE_FORK,
    WAIT_FORK
};

/****************************** FUNCTIONS *********************************/
/* PARSE */
/* EXIT */
/* TIME */
/* UTILS */
/* ROUTINE  */

// => parse.c
int						ft_parse(int argc, char **argv, t_table *table);

// => exit.c
void					ft_free(t_table *table);
void					free_philo(t_table *table);
int						msg_err(int key_error);

// => time
long long				get_time(void);
void					ft_wait(long long time_to_wait, t_table *table);

// => logging
void					msg_log(t_philo *philo, int code);

// => utils.c
void					set_end_simu(t_table *table);
int						end_simu(t_table *table);
void					synch_start(long long time_start);

// routine
void					*handle_life(void *table_ptr);
void					*routine(void *philo_ptr);


#endif