/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_think_sleep.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouar <alaaouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 06:18:16 by alaaouar          #+#    #+#             */
/*   Updated: 2024/11/05 18:52:30 by alaaouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_head.h"

int	unlock_forks(t_philo *philo)
{
	if (philo->id % 2 != 0)
	{
		pthread_mutex_unlock(philo->l_shopstick);
		pthread_mutex_unlock(philo->r_shopstick);
		return (0);
	}
	else
	{
		pthread_mutex_unlock(philo->r_shopstick);
		pthread_mutex_unlock(philo->l_shopstick);
		return (0);
	}
	return (1);
}

void	philo_eating(t_philo *philo)
{
	lock_forks(philo);
	pthread_mutex_lock(philo->mutex->monitor);
	philo->eating = 1;
	pthread_mutex_unlock(philo->mutex->monitor);
	if (philo->nb_eat == 0)
	{
		unlock_forks(philo);
		return ;
	}
	printf_mutex(" is eating", philo);
	pthread_mutex_lock(philo->mutex->monitor);
	philo->last_eat = ft_getcurrenttime();
	if (philo->nb_eat != -1)
		philo->nb_eat--;
	philo->eating = 1;
	pthread_mutex_unlock(philo->mutex->monitor);
	ft_usleep(philo->time_to_eat);
	pthread_mutex_lock(philo->mutex->monitor);
	philo->eating = 0;
	pthread_mutex_unlock(philo->mutex->monitor);
	unlock_forks(philo);
}

int	full_stomack(t_philo *philo)
{
	if (philo->nb_eat != -1)
	{
		pthread_mutex_lock(philo->mutex->monitor);
		if (philo->nb_eat == 0)
		{
			pthread_mutex_unlock(philo->mutex->monitor);
			return (1);
		}
		pthread_mutex_unlock(philo->mutex->monitor);
	}
	return (0);
}
