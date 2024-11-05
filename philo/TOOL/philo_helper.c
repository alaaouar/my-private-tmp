/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouar <alaaouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 21:57:51 by alaaouar          #+#    #+#             */
/*   Updated: 2024/11/05 22:03:41 by alaaouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INC/philo_head.h"

t_mutex	*shopsticks_init(int size, pthread_mutex_t *shop)
{
	t_mutex	*shopsticks;

	shopsticks = malloc(sizeof(t_mutex));
	if (!shopsticks)
		return (NULL);
	shopsticks->print = malloc(sizeof(pthread_mutex_t));
	if (!shopsticks->print)
		return (NULL);
	pthread_mutex_init(shopsticks->print, NULL);
	shopsticks->monitor = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!shopsticks->monitor)
	{
		return (NULL);
	}
	pthread_mutex_init(shopsticks->monitor, NULL);
	shopsticks->count_mtx = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!shopsticks->count_mtx)
		return (NULL);
	pthread_mutex_init(shopsticks->count_mtx, NULL);
	shopsticks->forks = shop;
	shopsticks->dead = 0;
	shopsticks->count = 0;
	shopsticks->size = size;
	return (shopsticks);
}

t_philo	*born_philo(t_init_args *args, pthread_mutex_t *r, pthread_mutex_t *l)
{
	t_philo		*philo;
	static int	i = 1;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->id = i;
	philo->nb_philo = ft_atoi(args->av[1]);
	philo->time_to_die = ft_atoi(args->av[2]);
	philo->time_to_eat = ft_atoi(args->av[3]);
	philo->time_to_sleep = ft_atoi(args->av[4]);
	if (args->ac == 6)
		philo->nb_eat = ft_atoi(args->av[5]);
	else
		philo->nb_eat = -1;
	philo->last_meal = (struct timeval){0};
	philo->start = 0;
	philo->eating = 0;
	philo->last_eat = 0;
	philo->r_shopstick = r;
	philo->l_shopstick = l;
	philo->mutex = args->mutex;
	philo->next = NULL;
	i++;
	return (philo);
}
