/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpollito <cpollito@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 14:41:05 by cpollito          #+#    #+#             */
/*   Updated: 2022/06/28 16:25:52 by cpollito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	*monitoring(void *the_philo)
{
	t_philo	*philo;

	philo = the_philo;
	while (true)
	{
		if (philo->time_must_eat == 0)
		{
			sem_post(philo->data->forks);
			sem_post(philo->data->forks);
			sem_post(philo->data->eat);
			exit (FULL);
		}
		if (time_program(philo->data->time_start) - philo->last_eat
			> philo->data->time_to_die)
		{
			sem_wait(philo->data->print_sms);
			printf ("%ld %d is dead\n", time_program(philo->data->time_start),
				philo->id_philo);
			exit(DEAD);
		}
		usleep(500);
	}
	return (OK);
}

void	monitiring_thread(t_philo *philo)
{
	pthread_t	monitor;

	if (pthread_create(&monitor, NULL, monitoring, philo))
		exit(EXIT_FAILURE);
	if (pthread_detach(monitor))
		exit (EXIT_FAILURE);
}

void	routine(t_philo *philo)
{
	monitiring_thread(philo);
	if (philo->id_philo % 2)
		my_usleep(philo->data->time_to_sleep);
	while (true)
	{
		sem_wait(philo->data->forks);
		f_print(philo, "has taken a fork\n");
		sem_wait(philo->data->forks);
		f_print(philo, "has taken a fork\n");
		f_print(philo, "is eating\n");
		philo->time_must_eat--;
		philo->last_eat = time_now() - philo->data->time_start;
		my_usleep(philo->data->time_to_eat);
		sem_post(philo->data->forks);
		sem_post(philo->data->forks);
		f_print(philo, "is sleeping\n");
		my_usleep(philo->data->time_to_sleep);
		f_print(philo, "is thinking\n");
	}
}
