/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouar <alaaouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 05:07:23 by alaaouar          #+#    #+#             */
/*   Updated: 2024/11/05 17:56:10 by alaaouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_head.h"

long long	ft_getcurrenttime(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = (size_t)ft_getcurrenttime();
	while (((size_t)ft_getcurrenttime() - start) < milliseconds)
		usleep(100);
	return (0);
}

void	printf_mutex(char *msg, t_philo *philo)
{
	pthread_mutex_lock(philo->mutex->monitor);
	if (philo->mutex->dead == 1)
	{
		pthread_mutex_unlock(philo->mutex->monitor);
		return ;
	}
	pthread_mutex_unlock(philo->mutex->monitor);
	pthread_mutex_lock(philo->mutex->print);
	printf ("=%lld= Philo %d%s \n", ft_getcurrenttime()
		-philo->start, philo->id, msg);
	pthread_mutex_unlock(philo->mutex->print);
}

int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->mutex->monitor);
	if (philo->mutex->dead == 1)
		return (pthread_mutex_unlock(philo->mutex->monitor), 1);
	return (pthread_mutex_unlock(philo->mutex->monitor), 0);
}

int	lock_forks(t_philo *philo)
{
	if (philo->id % 2 != 0)
	{
		pthread_mutex_lock(philo->l_shopstick);
		printf_mutex(" has taken a fork", philo);
		pthread_mutex_lock(philo->r_shopstick);
		printf_mutex(" has taken a fork", philo);
		return (0);
	}
	else
	{
		pthread_mutex_lock(philo->r_shopstick);
		printf_mutex(" has taken a fork", philo);
		pthread_mutex_lock(philo->l_shopstick);
		printf_mutex(" has taken a fork", philo);
		return (0);
	}
	return (1);
}
