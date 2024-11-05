/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_philos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouar <alaaouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 20:46:20 by alaaouar          #+#    #+#             */
/*   Updated: 2024/11/05 17:53:18 by alaaouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_head.h"

void	clean(t_philo *philo)
{
	t_philo	*tmp;

	tmp = philo;
	while (tmp)
	{
		pthread_mutex_destroy(tmp->r_shopstick);
		pthread_mutex_destroy(tmp->l_shopstick);
		tmp = tmp->next;
	}
	pthread_mutex_destroy(philo->mutex->print);
	pthread_mutex_destroy(philo->mutex->monitor);
	pthread_mutex_destroy(philo->mutex->count_mtx);
	free(philo->mutex->print);
	free(philo->mutex->monitor);
	free(philo->mutex->count_mtx);
	free(philo->mutex);
	free(philo->mutex->forks);
	free(philo);
}

void	set_time_food(t_philo *philo)
{
	pthread_mutex_lock(philo->mutex->monitor);
	philo->start = ft_getcurrenttime();
	philo->last_eat = philo->start;
	pthread_mutex_unlock(philo->mutex->monitor);
}

void	*casual_day(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	set_time_food(philo);
	if (philo->id % 2 == 0)
		ft_usleep(philo->time_to_eat - 10);
	if (philo->nb_philo == 1)
	{
		printf_mutex(" died", philo);
		return (NULL);
	}
	while (!is_dead(philo))
	{
		philo_eating(philo);
		if (full_stomack(philo))
			break ;
		philo_sleeping(philo, philo->time_to_sleep);
		philo_thinking(philo);
	}
	pthread_mutex_lock(philo->mutex->count_mtx);
	philo->mutex->count++;
	pthread_mutex_unlock(philo->mutex->count_mtx);
	return (NULL);
}

void	spawn_philo(t_philo *philo)
{
	t_philo		*tmp;
	pthread_t	observer;

	tmp = philo;
	while (tmp)
	{
		pthread_create(&tmp->threads, NULL, casual_day, (void *)tmp);
		tmp = tmp->next;
	}
	tmp = philo;
	pthread_create(&observer, NULL, observer_rout, (void *)tmp);
	pthread_detach(observer);
	while (tmp)
	{
		pthread_join(tmp->threads, NULL);
		tmp = tmp->next;
	}
	tmp = philo;
	if (tmp->mutex->count == tmp->nb_philo)
		clean(philo);
}
