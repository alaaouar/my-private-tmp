/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   everything_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouar <alaaouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 18:29:11 by alaaouar          #+#    #+#             */
/*   Updated: 2024/11/05 18:56:07 by alaaouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_head.h"

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

t_philo	*born_philo(char **av, int ac, t_mutex *mutex,
	pthread_mutex_t *r, pthread_mutex_t *l)
{
	t_philo	*philo;
	static int i = 1;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->id = i;
	philo->nb_philo = ft_atoi(av[1]);
	philo->time_to_die = ft_atoi(av[2]);
	philo->time_to_eat = ft_atoi(av[3]);
	philo->time_to_sleep = ft_atoi(av[4]);
	philo->nb_eat = (ac == 6) ? ft_atoi(av[5]) : -1;
	philo->last_meal = (struct timeval){0};
	philo->start = 0;
	philo->eating = 0;
	philo->last_eat = 0;
	philo->r_shopstick = r;
	philo->l_shopstick = l;
	philo->mutex = mutex;
	philo->next = NULL;
	i++;
	return (philo);
}

void	attach_next(t_philo **philo, t_philo *new, t_mutex *mutex)
{
	t_philo	*tmp;

	if (!*philo)
	{
		*philo = new;
		(*philo)->mutex = mutex;
		return ;
	}
	tmp = *philo;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->mutex = mutex;
}

void    init_shop(pthread_mutex_t **shop, int size)
{
    int i;

    *shop = malloc(sizeof(pthread_mutex_t) * size);
    if (!*shop)
    {
        printf("Error: malloc failed\n");
        return;
    }
    i = 0;
    while (i < size)
        pthread_mutex_init(&(*shop)[i++], NULL);
}

t_mutex *init_mutex(int size, pthread_mutex_t *shop)
{
    t_mutex *mutex;

    mutex = shopsticks_init(size, shop);
    if (!mutex)
    {
        printf("Error: malloc failed\n");
        return NULL;
    }
    return mutex;
}

void    create_philos(t_init_args *args)
{
    t_philo *tmp;
    int     i;

    i = 0;
    while (i < args->size)
    {
        if (i == args->size - 1)
            tmp = born_philo(args->av, args->ac, args->mutex, &args->shop[i], &args->shop[0]);
        else
            tmp = born_philo(args->av, args->ac, args->mutex, &args->shop[i], &args->shop[i + 1]);
        if (!tmp)
        {
            *(args->philo) = NULL;
            printf("Error: malloc failed\n");
            return;
        }
        attach_next(args->philo, tmp, args->mutex);
        i++;
    }
}

void    everything_init(char **av, int ac, t_philo **philo)
{
    t_init_args args;

    args.av = av;
    args.ac = ac;
    args.philo = philo;
    args.size = ft_atoi(av[1]);

    init_shop(&args.shop, args.size);
    if (!args.shop)
    {
        *philo = NULL;
        return;
    }
    args.mutex = init_mutex(args.size, args.shop);
    if (!args.mutex)
    {
        *philo = NULL;
        return;
    }
    create_philos(&args);
}
