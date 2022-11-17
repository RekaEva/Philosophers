/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpollito <cpollito@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 14:37:27 by cpollito          #+#    #+#             */
/*   Updated: 2022/06/17 17:40:58 by cpollito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	time_now(void)
{
	struct timeval	start;
	long			ms;

	gettimeofday(&start, NULL);
	ms = start.tv_sec * 1000 + start.tv_usec / 1000;
	return (ms);
}

long	time_program(long time_start)
{
	long	cur_ms;

	cur_ms = time_now() - time_start;
	return (cur_ms);
}

void	my_usleep(long ms)
{
	long	start;
	long	current;

	start = time_now();
	current = time_now();
	while (ms > current - start)
	{
		usleep(1000);
		current = time_now();
	}
}
