/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpollito <cpollito@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 14:12:06 by cpollito          #+#    #+#             */
/*   Updated: 2022/06/28 16:33:49 by cpollito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h" 

static int	check_eat(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		if (data->philos[i]->time_must_eat != 0)
			return (0);
		i++;
	}
	return (1);
}

int	alive_or_dead(t_data *data, int i)
{
	if (time_program(data->time_start) - data->philos[i]->last_eat
		> data->time_to_die)
	{
		data->stop = 1;
		pthread_mutex_unlock(&data->stat_mtx);
		pthread_mutex_lock(&data->print_mutex);
		printf("%ld philo %d is dead\n",
			time_program (data->time_start), data->philos[i]->id_philo);
		return (1);
	}
	return (0);
}

int	monitoring(t_data *data)
{
	int	i;

	while (true)
	{
		i = 0;
		pthread_mutex_lock(&data->stat_mtx);
		while (i < data->n_philo)
		{
			if (check_eat(data))
			{
				pthread_mutex_unlock(&data->stat_mtx);
				return (1);
			}
			if (alive_or_dead(data, i) == 1)
				return (1);
			i++;
		}
		pthread_mutex_unlock(&data->stat_mtx);
		usleep(500);
	}
	return (0);
}
