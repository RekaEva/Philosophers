/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_begins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpollito <cpollito@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 14:16:21 by cpollito          #+#    #+#             */
/*   Updated: 2022/06/28 15:37:06 by cpollito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	destroy_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		pthread_mutex_unlock(&data->all_forks[i]);
		if (pthread_mutex_destroy(&data->all_forks[i]))
			return (1);
		i++;
	}
	if (pthread_mutex_destroy(&data->print_mutex))
		return (1);
	if (pthread_mutex_destroy(&data->stat_mtx))
		return (1);
	return (0);
}

int	dinner_begins(t_data *data)
{
	int	i;

	if (get_memmory(data) == ERROR)
		return (ERROR);
	data->time_start = time_now();
	i = -1;
	while (++i < data->n_philo)
	{
		data->philos[i] = init_philo(data, i);
		if (!data->philos)
			return (ERROR);
		if (pthread_create(&data->threads[i], NULL,
				philosophical_routine, (void *)data->philos[i]))
			return (ERROR);
		if (pthread_detach(data->threads[i]))
			return (ERROR);
	}
	if (monitoring(data))
	{
		if (destroy_mutexes(data))
			return (ERROR);
	}
	return (OK);
}
