/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpollito <cpollito@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 13:40:35 by cpollito          #+#    #+#             */
/*   Updated: 2022/06/28 14:47:56 by cpollito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	get_memmory(t_data *data)
{
	data->threads = malloc(sizeof(pthread_t) * data->n_philo);
	if (!data->threads)
	{
		free(data->all_forks);
		free(data);
		printf ("Error:\nmalloc threads error\n");
		return (ERROR);
	}
	data->philos = malloc(sizeof (t_philo) * data->n_philo);
	if (!data->philos)
	{
		free(data->all_forks);
		free(data->threads);
		free(data);
		printf ("Error:\nmalloc philos error\n");
		return (ERROR);
	}
	return (OK);
}

t_philo	*init_philo(t_data *data, int i)
{
	data->philos[i] = malloc(sizeof (t_philo));
	if (!data->philos[i])
	{
		free_data(data, i);
		printf ("Error:\nmalloc error philos i=%d", i);
		return (NULL);
	}
	data->philos[i]->right_f = i;
	if (data->n_philo > 1)
	{
		data->philos[i]->left_f = i;
		if (i < (data->n_philo - 1))
			data->philos[i]->left_f = i + 1;
		else
			data->philos[i]->left_f = 0;
	}
	else
		data->philos[i]->left_f = i;
	data->philos[i]->id_philo = i + 1;
	data->philos[i]->data = data;
	data->philos[i]->last_eat = 0;
	data->philos[i]->time_must_eat = data->time_must_eat;
	return (data->philos[i]);
}

void	free_forks_failed(t_data *data)
{
	free(data->all_forks);
	free(data);
}

t_mutex	*ft_init_forks(t_data *data)
{
	t_mutex	*all_forks;
	int		i;

	all_forks = malloc(sizeof (t_mutex) * data->n_philo);
	if (!all_forks)
	{
		free(data);
		return (NULL);
	}
	i = -1;
	while (++i < data->n_philo)
	{
		if (pthread_mutex_init(&all_forks[i], NULL))
		{
			free_forks_failed(data);
			return (NULL);
		}
	}
	if (pthread_mutex_init(&data->print_mutex, NULL)
		|| pthread_mutex_init(&data->stat_mtx, NULL))
	{
		free_forks_failed(data);
		return (NULL);
	}
	return (all_forks);
}

t_data	*ft_init_data(char **argv)
{
	t_data	*data;

	data = malloc(sizeof (t_data));
	if (!data)
		return (NULL);
	data->n_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (!argv[5])
		data->time_must_eat = -1;
	else
		data->time_must_eat = ft_atoi(argv[5]);
	data->stop = 0;
	if (pthread_mutex_init(&data->stat_mtx, NULL)
		|| !data->n_philo || !data->time_to_die || !data->time_must_eat
		|| !data->time_to_sleep || !data->time_to_eat)
	{
		free(data);
		return (NULL);
	}
	return (data);
}
