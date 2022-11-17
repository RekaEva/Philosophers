/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpollito <cpollito@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 13:08:19 by cpollito          #+#    #+#             */
/*   Updated: 2022/06/17 15:46:10 by cpollito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_check_arguments(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
			{
				printf ("Error:\nWrong type of arguments!\n");
				return (ERROR);
			}
			j++;
		}
		i++;
	}
	return (OK);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc == 5 || argc == 6)
	{
		if (ft_check_arguments(argv) == ERROR)
			return (EXIT_FAILURE);
		data = ft_init_data(argv);
		if (!data)
			return (EXIT_FAILURE);
		data->all_forks = ft_init_forks(data);
		if (!data->all_forks)
			return (EXIT_FAILURE);
		if (dinner_begins(data) == ERROR)
			return (EXIT_FAILURE);
		free_data(data, data->n_philo);
	}
	else
	{
		printf("Error:\nwrong number of argument\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
