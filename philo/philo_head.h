/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_head.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouar <alaaouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 18:13:01 by alaaouar          #+#    #+#             */
/*   Updated: 2024/11/04 18:27:22 by alaaouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_HEAD_H
# define PHILO_HEAD_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

#define MAX_INT 2147483647
#define MIN_INT -2147483648

typedef struct s_philosopher t_philosopher;

typedef struct s_mutex
{
	pthread_mutex_t	*print;
	pthread_mutex_t	*monitor;
	pthread_mutex_t	*count_mtx;
	pthread_mutex_t	*forks;
	int				dead;
	int				count;
	int				size;
}					t_mutex;

typedef struct s_philo
{
	int				id;
	long long		nb_philo;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				nb_eat;
	struct timeval	last_meal;
	long long		start;
	int				eating;
	long long		last_eat;
	pthread_t		threads;
	pthread_mutex_t	*r_shopstick;
	pthread_mutex_t	*l_shopstick;
	t_mutex			*mutex;
	struct s_philo	*next;
}					t_philo;


int	parse(char **av);

#endif