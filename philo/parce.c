/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouar <alaaouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 18:15:25 by alaaouar          #+#    #+#             */
/*   Updated: 2024/11/05 17:47:09 by alaaouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_head.h"

int	ft_isdigit(int car)
{
	if (car >= '0' && car <= '9')
		return (1);
	return (0);
}

int	numbers_only(char **str)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if ((str[i][j] == '-' || str[i][j] == '+') && j == 0)
			{
				j++;
				continue ;
			}
			if (!ft_isdigit(str[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	long	i;
	int		s;
	long	o;

	i = 0;
	o = 0;
	s = 1;
	while ((str[i] != '\0') && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '-' && (str[i + 1] >= '0' && str[i + 1] <= '9'))
	{
		i++;
		s = -1;
	}
	if (str[i] == '+' && (str[i + 1] >= '0' && str[i + 1] <= '9'))
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		o *= 10;
		o += str[i] - 48;
		i++;
	}
	o *= s;
	return (o);
}

int	parse(char **av)
{
	if (numbers_only(av))
		return (1);
	if (ft_atoi(av[1]) < 2 || ft_atoi(av[1]) > 200)
		return (1);
	if (ft_atoi(av[2]) < 60 || ft_atoi(av[2]) > MAX_INT)
		return (1);
	if (ft_atoi(av[3]) < 60 || ft_atoi(av[3]) > MAX_INT)
		return (1);
	if (ft_atoi(av[4]) < 60 || ft_atoi(av[4]) > MAX_INT)
		return (1);
	if (av[5] && (ft_atoi(av[5]) < 0 || ft_atoi(av[5]) > MAX_INT))
		return (1);
	return (0);
}
