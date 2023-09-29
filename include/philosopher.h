/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 15:28:29 by uclement          #+#    #+#             */
/*   Updated: 2023/09/29 15:16:30 by uclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <unistd.h>
# include <stdlib.h>
# include <inttypes.h>
# include "libft.h"
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>

struct s_data;

typedef struct s_philo {
	struct s_data	*data;
	int				id;
	int				count_meal;
	int				is_eating;
	int				must_eat;
	u_int64_t				ttdie;
	u_int64_t				tteat;
	u_int64_t		lastmeal;
	u_int64_t		start;
	pthread_t		thread;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	test;
	pthread_mutex_t	philo_lock;
}	t_philo;

typedef struct s_data {
	int						count;
	u_int64_t				ttdie;
	u_int64_t				tteat;
	u_int64_t				ttsleep;
	u_int64_t				start;
	int						must_eat;
	int				dead;
	pthread_t		watcher;
	pthread_mutex_t	*fork;
	t_philo			*philo;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	print;
}	t_data;



//init
void	init_philo(t_data	*data, pthread_mutex_t *forks);
void	init_forks(pthread_mutex_t *forks, char nb_philo);
void	init_data(t_data *data, char **av);
void	init_all(t_data *data, char **av);

//utils
size_t	get_current_time(void);
int	ft_usleep(size_t milliseconds);

//process
void	eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	*routine(void *philo_ptr);
void	print_txt(t_philo *philo, char *str);

//threads
void	threads_maker(t_data *data);
void	threads_breaker(t_data *data);
int is_dead(t_data *data);
int	check_death(t_philo *philo);
int	loop_death(t_philo *philo);

#endif