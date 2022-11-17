/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpollito <cpollito@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 13:07:22 by cpollito          #+#    #+#             */
/*   Updated: 2022/06/28 14:38:51 by cpollito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdbool.h>

# define OK 0
# define ERROR -1

typedef pthread_mutex_t	t_mutex;
typedef struct s_philo	t_philo;

typedef struct s_data
{
	int			n_philo;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			time_must_eat;
	long		time_start;
	int			stop;
	pthread_t	*threads;
	t_mutex		*all_forks;
	t_mutex		print_mutex;
	t_mutex		stat_mtx;
	t_philo		**philos;
}				t_data;

typedef struct s_philo
{
	int		id_philo;
	int		left_f;
	int		right_f;
	long	last_eat;
	int		time_must_eat;
	t_data	*data;
}				t_philo;

// utils
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
void	free_data(t_data *data, int i);
void	f_print(t_philo *philo, char *sms);

//init
t_data	*ft_init_data(char **argv);
t_mutex	*ft_init_forks(t_data *data);
t_philo	*init_philo(t_data *data, int i);
int		get_memmory(t_data *data);

//dinner_begins
int		dinner_begins(t_data *data);

//routine
void	*philosophical_routine(void *the_philo);

// monitoring
int		monitoring(t_data *data);

//time
long	time_now(void);
long	time_program(long time_start);
void	my_usleep(long ms);

#endif