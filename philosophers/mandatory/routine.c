/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpollito <cpollito@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 14:41:05 by cpollito          #+#    #+#             */
/*   Updated: 2022/06/28 16:06:27 by cpollito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->stat_mtx);
	if (philo->data->stop || philo->time_must_eat == 0)
	{
		pthread_mutex_unlock(&philo->data->stat_mtx);
		return ;
	}
	pthread_mutex_unlock(&philo->data->stat_mtx);
	f_print(philo, "is thinking\n");
}

void	sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->stat_mtx);
	if (philo->data->stop || philo->time_must_eat == 0)
	{
		pthread_mutex_unlock(&philo->data->stat_mtx);
		return ;
	}
	pthread_mutex_unlock(&philo->data->stat_mtx);
	f_print(philo, "is sleeping\n");
	my_usleep(philo->data->time_to_sleep);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->stat_mtx);
	if (philo->data->stop || philo->time_must_eat == 0)
	{
		pthread_mutex_unlock(&philo->data->stat_mtx);
		return ;
	}
	philo->last_eat = time_now() - philo->data->time_start;
	philo->time_must_eat--;
	pthread_mutex_unlock(&philo->data->stat_mtx);
	f_print(philo, "is eating\n");
	my_usleep(philo->data->time_to_eat);
	if (philo->right_f < philo->left_f)
	{
		pthread_mutex_unlock(&philo->data->all_forks[philo->left_f]);
		pthread_mutex_unlock(&philo->data->all_forks[philo->right_f]);
	}
	else
	{
		pthread_mutex_unlock(&philo->data->all_forks[philo->right_f]);
		pthread_mutex_unlock(&philo->data->all_forks[philo->left_f]);
	}
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->stat_mtx);
	if (philo->data->stop == 1 || philo->time_must_eat == 0)
	{
		pthread_mutex_unlock(&philo->data->stat_mtx);
		return ;
	}
	pthread_mutex_unlock(&philo->data->stat_mtx);
	if (philo->id_philo == 0)
	{
		pthread_mutex_lock(&philo->data->all_forks[philo->right_f]);
		f_print(philo, "has taken a fork\n");
		pthread_mutex_lock(&philo->data->all_forks[philo->left_f]);
		f_print(philo, "has taken a fork\n");
	}
	else
	{
		pthread_mutex_lock(&philo->data->all_forks[philo->left_f]);
		f_print(philo, "has taken a fork\n");
		pthread_mutex_lock(&philo->data->all_forks[philo->right_f]);
		f_print(philo, "has taken a fork\n");
	}
}

void	*philosophical_routine(void *the_philo)
{
	t_philo	*philo;

	philo = the_philo;
	if (philo->id_philo % 2 == 0)
		sleeping(philo);
	while (true)
	{
		pthread_mutex_lock(&philo->data->stat_mtx);
		if (philo->data->stop)
		{
			pthread_mutex_unlock(&philo->data->stat_mtx);
			break ;
		}
		pthread_mutex_unlock(&philo->data->stat_mtx);
		take_forks(philo);
		eating(philo);
		if (philo->time_must_eat == 0)
			break ;
		sleeping(philo);
		thinking(philo);
	}
	return (OK);
}
