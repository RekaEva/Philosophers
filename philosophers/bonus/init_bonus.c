/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpollito <cpollito@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 13:40:35 by cpollito          #+#    #+#             */
/*   Updated: 2022/06/28 16:27:45 by cpollito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	init_sem(t_data *data)
{
	sem_unlink("/print_sms");
	sem_unlink("/forks");
	data->print_sms = sem_open("/print_sms", O_CREAT | O_EXCL, 0777, 1);
	if (data->print_sms == SEM_FAILED)
		return (ERROR);
	data->forks = sem_open("/forks", O_CREAT | O_EXCL, 0777, data->n_philo);
	if (data->forks == SEM_FAILED)
		return (ERROR);
	return (OK);
}

int	get_memmory(t_data *data)
{
	data->philos = malloc(sizeof (t_philo) * data->n_philo);
	if (!data->philos)
	{
		free(data);
		printf ("Error:\nmalloc philos error\n");
		return (ERROR);
	}
	data->pid = malloc(sizeof (pid_t) * data->n_philo);
	if (!data->pid)
	{
		free(data->philos);
		free(data);
		printf ("Error:\nmalloc pid error\n");
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
	data->philos[i]->id_philo = i + 1;
	data->philos[i]->data = data;
	data->philos[i]->last_eat = 0;
	data->philos[i]->time_must_eat = data->time_must_eat;
	return (data->philos[i]);
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
	if (!data->n_philo || !data->time_to_die || !data->time_must_eat
		|| !data->time_to_eat || !data->time_to_sleep)
	{
		free(data);
		return (NULL);
	}
	return (data);
}
