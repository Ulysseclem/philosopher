/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 21:29:33 by ulysseclem        #+#    #+#             */
/*   Updated: 2023/09/27 17:42:00 by uclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"


int	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->philo_lock);
	if(philo->data->dead == 1)
		return (1);
	pthread_mutex_unlock(&philo->philo_lock);
	return (0);
}

int is_dead(t_data *data)
{
	int	i;

	pthread_mutex_lock(&data->dead_lock);
	i = 0;
	while (i < data->count)
	{
		if (((data->philo[i].lastmeal + data->ttdie) < get_current_time())  && data->philo[i].is_eating == 0)
		{
			print_txt(&data->philo[i], "has died");
			data->dead = 1;
			return(1);
		}
		i++;
	}
	pthread_mutex_unlock(&data->dead_lock);
	return (0);
}

void	*watcher(void *data_ptr)
{
	t_data	*data;

	data = (t_data *)data_ptr;
	while (1)
	{
		ft_usleep(5);
		if ((is_dead(data) == 1))
			break ;
	}
	return (data_ptr);
}

void	threads_breaker(t_data *data)
{
	int	i;

	i = -1;
	// while (++i < data->count)
	// 	pthread_mutex_destroy(&data->forks[i]);
	pthread_mutex_destroy(&data->dead_lock);
}

void	threads_maker(t_data *data)
{
	int	i;
	
	i = 0;
	// pthread_create(&data->watcher, NULL, &watcher, data);
	while (i < data->count)
	{
		pthread_create(&data->philo[i].thread, NULL, &routine, &data->philo[i]);
		i++;
	}
	// pthread_join(data->watcher, NULL);
	i = -1;
	while (++i < data->count)
		pthread_join(data->philo[i].thread, NULL);
}