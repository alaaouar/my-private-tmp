/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observe_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouar <alaaouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 05:04:20 by alaaouar          #+#    #+#             */
/*   Updated: 2024/11/05 06:56:26 by alaaouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_head.h"

void	obs_death_handle(t_philo *tmp)
{
	pthread_mutex_lock(tmp->mutex->print);
	printf("[%lld] Philo %d died\n", ft_getcurrenttime() - tmp->start, tmp->id);
	pthread_mutex_unlock(tmp->mutex->print);
	tmp->mutex->dead = 1;
	pthread_mutex_unlock(tmp->mutex->monitor);
}

int	observer_tracker(t_philo **philo)
{
	t_philo	*tmp;

	tmp = *philo;
	if (!tmp->mutex->dead && (ft_getcurrenttime()
			- tmp->last_eat >= tmp->time_to_die) && tmp->eating == 0)
		return (obs_death_handle(tmp), 1);
	pthread_mutex_unlock(tmp->mutex->monitor);
	*philo = (*philo)->next;
	return (0);
}

void    *observer_rout(void *arg)
{
	t_philo	*tmp;
	t_philo	*philo;

	tmp = (t_philo *)arg;
	(usleep(50), philo = (t_philo *)arg);
	while (1)
	{
		while (tmp)
		{
			pthread_mutex_lock(tmp->mutex->count_mtx);
			if (philo->mutex->count == philo->nb_philo)
				return (NULL);
			(pthread_mutex_unlock(tmp->mutex->count_mtx),
				pthread_mutex_lock(tmp->mutex->monitor));
			if (tmp->nb_eat == 0)
			{
				(pthread_mutex_unlock(tmp->mutex->monitor), tmp = tmp->next);
				continue ;
			}
			if (observer_tracker(&tmp))
				return (NULL);
		}
		tmp = philo;
	}
	return (NULL);
}
