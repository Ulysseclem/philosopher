/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulysseclem <ulysseclem@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 20:35:09 by ulysseclem        #+#    #+#             */
/*   Updated: 2023/09/26 23:01:10 by ulysseclem       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	init_philo(t_data	*data, pthread_mutex_t *forks)
{
	int i;

	i = 0;
	while (i < data->count)
	{
		data->philo[i].id = i + 1;
		data->philo[i].data = data;
		data->philo[i].start = get_current_time();
		data->philo[i].lastmeal = get_current_time();
		data->philo[i].count_meal = 0;
		data->philo[i].l_fork = &forks[data->philo[i].id - 1];
		if (data->philo[i].id == 1)
			data->philo[i].r_fork = &forks[data->count - 1];
		if (data->philo[i].id > 1)
			data->philo[i].r_fork = &forks[data->philo[i].id - 2];
		i++;
	}
}

void	init_forks(pthread_mutex_t *forks, char nb_philo)
{
	int i;

	i = 0;
	while (i < nb_philo)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void	init_data(t_data *data, char **av)
{
	data->count = ft_atoi(av[1]);
	data->ttdie = (u_int64_t)ft_atoi(av[2]);
	data->tteat = (u_int64_t)ft_atoi(av[3]);
	data->ttsleep = (u_int64_t)ft_atoi(av[4]);
	data->must_eat = ft_atoi(av[5]);
	data->dead = 0;
	// pthread_mutex_init(&data->dead_lock, NULL);
}

void	init_all(t_data *data, char **av)
{
	t_philo			*philo;

	init_data(data, av);
	philo = malloc(sizeof(t_philo) * data->count);
	data->philo = philo;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->count);
	init_forks(data->forks, data->count);
	init_philo(data, data->forks);
}