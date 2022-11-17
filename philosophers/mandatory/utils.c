/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpollito <cpollito@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 13:33:03 by cpollito          #+#    #+#             */
/*   Updated: 2022/06/28 16:33:35 by cpollito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_philo(t_data *data, int i)
{
	while (i > 0)
	{
		free(data->philos[i - 1]);
		i--;
	}
	free(data->philos);
}

void	free_data(t_data *data, int i)
{
	free(data->all_forks);
	free(data->threads);
	free_philo(data, i);
	free(data);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_atoi(const char *str)
{
	int		i;
	long	result;
	int		znak;

	i = 0;
	result = 0;
	znak = 1;
	while ((str[i] == 32) || ((str[i] >= 9) && (str[i] <= 13)))
		i++;
	if (str[i] && (str[i] == '-' || str[i] == '+'))
	{
		if (str[i] == '-')
		{
			znak = -1;
		}
		i++;
	}
	while ((str[i] >= '0') && (str[i] <= '9'))
	{
		result = result * 10;
		result = result + (str[i] - '0');
		i++;
	}
	return (result * znak);
}

void	f_print(t_philo *philo, char *sms)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	printf ("%ld %d %s", time_program(philo->data->time_start),
		philo->id_philo, sms);
	pthread_mutex_unlock(&philo->data->print_mutex);
}
