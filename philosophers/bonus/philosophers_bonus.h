/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpollito <cpollito@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 13:07:22 by cpollito          #+#    #+#             */
/*   Updated: 2022/06/28 16:25:26 by cpollito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdbool.h>
# include <semaphore.h>
# include <sys/wait.h>
# include <signal.h>

# define OK 0
# define ERROR -1
# define FULL 1
# define DEAD 2

typedef struct s_philo	t_philo;

typedef struct s_data
{
	int			n_philo;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			time_must_eat;
	long		time_start;
	pid_t		*pid;
	sem_t		*forks;
	sem_t		*print_sms;
	sem_t		*death;
	sem_t		*eat;
	t_philo		**philos;
}				t_data;

typedef struct s_philo
{
	int		id_philo;
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
t_philo	*init_philo(t_data *data, int i);
int		get_memmory(t_data *data);
int		init_sem(t_data *data);

//dinner_begins
int		dinner_begins(t_data *data);

//routine
void	routine(t_philo *philo);

//time
long	time_now(void);
long	time_program(long time_start);
void	my_usleep(long ms);

#endif
