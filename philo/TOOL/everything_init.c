/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   everything_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouar <alaaouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 18:29:11 by alaaouar          #+#    #+#             */
/*   Updated: 2024/11/05 22:03:30 by alaaouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INC/philo_head.h"

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

void	init_shop(pthread_mutex_t **shop, int size)
{
	int	i;

	*shop = malloc(sizeof(pthread_mutex_t) * size);
	if (!*shop)
	{
		printf ("Error: malloc failed\n");
		return ;
	}
	i = 0;
	while (i < size)
		pthread_mutex_init(&(*shop)[i++], NULL);
}

t_mutex	*init_mutex(int size, pthread_mutex_t *shop)
{
	t_mutex	*mutex;

	mutex = shopsticks_init(size, shop);
	if (!mutex)
	{
		printf("Error: malloc failed\n");
		return (NULL);
	}
	return (mutex);
}

void	create_philos(t_init_args *args)
{
	t_philo	*tmp;
	int		i;

	i = 0;
	while (i < args->size)
	{
		if (i == args->size - 1)
			tmp = born_philo(args, &args->shop[i], &args->shop[0]);
		else
			tmp = born_philo(args, &args->shop[i], &args->shop[i + 1]);
		if (!tmp)
		{
			*(args->philo) = NULL;
			printf("Error: malloc failed\n");
			return ;
		}
		attach_next(args->philo, tmp, args->mutex);
		i++;
	}
}

void	everything_init(char **av, int ac, t_philo **philo)
{
	t_init_args	args;

	args.av = av;
	args.ac = ac;
	args.philo = philo;
	args.size = ft_atoi(av[1]);
	init_shop(&args.shop, args.size);
	if (!args.shop)
	{
		*philo = NULL;
		return ;
	}
	args.mutex = init_mutex(args.size, args.shop);
	if (!args.mutex)
	{
		*philo = NULL;
		return ;
	}
	create_philos(&args);
}
