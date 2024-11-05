/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_head.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouar <alaaouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 18:13:01 by alaaouar          #+#    #+#             */
/*   Updated: 2024/11/05 18:55:11 by alaaouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_HEAD_H
# define PHILO_HEAD_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

# define MAX_INT 2147483647
# define MIN_INT -2147483648

typedef struct s_philosopher	t_philosopher;

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

typedef struct s_init_args
{
    char            **av;
    int             ac;
    t_philo         **philo;
    t_mutex         *mutex;
    pthread_mutex_t *shop;
    int             size;
}               t_init_args;

int			parse(char **av);
int			ft_atoi(const char *str);
void		*observer(void *arg);
long long	ft_getcurrenttime(void);
int			ft_usleep(size_t milliseconds);
long long	ft_getcurrenttime(void);
int			is_dead(t_philo *philo);
void		printf_mutex(char *msg, t_philo *philo);
void		obs_death_handle(t_philo *tmp);
int			observer_tracker(t_philo **philo);
void		*observer_rout(void *arg);
void		clean(t_philo *philo);
void		*casual_day(void *arg);
void		spawn_philo(t_philo *philo);
void		philo_eating(t_philo *philo);
int			full_stomack(t_philo *philo);
int			unlock_forks(t_philo *philo);
void		philo_sleeping(t_philo *philo, long long time);
void		philo_thinking(t_philo *philo);
void		everything_init(char **av, int ac, t_philo **philo);
int			lock_forks(t_philo *philo);

#endif