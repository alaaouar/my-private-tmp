/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_philos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouar <alaaouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 20:46:20 by alaaouar          #+#    #+#             */
/*   Updated: 2024/11/04 20:59:02 by alaaouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_head.h"

void    clean(t_philo *philo)
{
    t_philo *tmp;

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

void    casual_day(void *arg)
{
    
}

void    observer(void *arg)
{
    t_philo *philo;
    t_philo *tmp;
    struct timeval now;

    philo = (t_philo *)arg;
    while (1)
    {
        tmp = philo;
        while (tmp)
        {
            gettimeofday(&now, NULL);
            if (tmp->eating && (now.tv_sec * 1000 + now.tv_usec / 1000) - tmp->last_eat > tmp->mutex->time_to_die)
            {
                pthread_mutex_lock(tmp->mutex->print);
                printf("%lld %d died\n", (now.tv_sec * 1000 + now.tv_usec / 1000) - tmp->mutex->start, tmp->id);
                pthread_mutex_unlock(tmp->mutex->print);
                tmp->mutex->dead = 1;
                return ;
            }
            tmp = tmp->next;
        }
    }
}

void    spawn_philo(t_philo *philo)
{
    t_philo *tmp;
    pthread_t observer;
    int i;

    i = 0;
    tmp = philo;
    while (tmp)
    {
        pthread_create(&tmp->threads, NULL, casual_day, (void *)tmp);
        tmp = tmp->next;
    }
    tmp = philo;
    pthread_create(&observer, NULL, observer, (void *)tmp);
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
