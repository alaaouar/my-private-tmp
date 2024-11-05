/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouar <alaaouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 18:02:23 by alaaouar          #+#    #+#             */
/*   Updated: 2024/11/05 22:04:01 by alaaouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INC/philo_head.h"

int	main(int ac, char **av)
{
	t_philo	*philo;

	philo = NULL;
	if (ac < 5 || ac > 6)
	{
		printf("Error: Wrong number of arguments\n");
		return (1);
	}
	else if (parse(av))
	{
		printf("Error Wrong arguments\n");
		return (1);
	}
	everything_init(av, ac, &philo);
	spawn_philo(philo);
	return (0);
}
