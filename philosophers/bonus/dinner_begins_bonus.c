/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_begins_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpollito <cpollito@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 14:16:21 by cpollito          #+#    #+#             */
/*   Updated: 2022/06/28 16:25:36 by cpollito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	kill_and_close(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		kill(data->pid[i], SIGTERM);
		i++;
	}
}

int	dinner_finish(t_data *data)
{
	int	status;
	int	eat;
	int	i;

	status = 0;
	eat = 0;
	i = 0;
	while (i < data->n_philo)
	{
		waitpid(-1, &status, 0);
		status = WEXITSTATUS(status);
		if (status == DEAD)
			kill_and_close(data);
		i++;
	}
	sem_close(data->forks);
	sem_unlink("/forks");
	sem_close(data->print_sms);
	sem_unlink("/print_sms");
	return (OK);
}

int	dinner_begins(t_data *data)
{
	int		i;
	pid_t	pid2;

	if (get_memmory(data) == ERROR)
		return (ERROR);
	data->time_start = time_now();
	i = 0;
	while (i < data->n_philo)
	{
		data->philos[i] = init_philo(data, i);
		pid2 = fork();
		if (pid2 == 0)
			routine(data->philos[i]);
		else if (pid2 == -1)
		{
			printf ("Error:\n fork error\n");
			return (ERROR);
		}
		else
			data->pid[i] = pid2;
		i++;
	}
	if (dinner_finish(data) == ERROR)
		return (ERROR);
	return (OK);
}
