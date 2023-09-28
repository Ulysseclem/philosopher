/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 21:29:33 by ulysseclem        #+#    #+#             */
/*   Updated: 2023/09/28 17:59:20 by uclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"


int	loop_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->dead_lock);
	if(	philo->data->dead == 1)
	{
		pthread_mutex_unlock(&philo->data->dead_lock);
		return(1);
	}
	pthread_mutex_unlock(&philo->data->dead_lock);
	return(0);	
}

int	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->test);
	if (((philo->lastmeal + philo->ttdie) < get_current_time())  && philo->is_eating == 0)
	{
		pthread_mutex_unlock(&philo->test);
		return(1);
	}
	pthread_mutex_unlock(&philo->test);
	return (0);
}


void	threads_breaker(t_data *data)
{
	// int	i;

	// i = -1;
	// while (++i < data->count)
	// 	pthread_mutex_destroy(&data->forks[i]);
	pthread_mutex_destroy(&data->dead_lock);
}

void	*watcher(void *data_ptr)
{
	t_data	*data;
	int	i;
	int	j = 0;

	data = (t_data *)data_ptr;
	while(1)
	{
		i = 0;
		while (i < data->count)
		{
			if (check_death(&data->philo[i]) == 1)
			{
				print_txt(&data->philo[i], "died");
				pthread_mutex_lock(&data->dead_lock);
				data->dead = 1;
				pthread_mutex_unlock(&data->dead_lock);
				return(NULL);
			}
			i++;
		}
		// ft_usleep(5);
		j++;
	}
	return(NULL);
}

void	threads_maker(t_data *data)
{
	int	i;
	
	i = 0;
	while (i < data->count)
	{
		pthread_create(&data->philo[i].thread, NULL, &routine, &data->philo[i]);
		i++;
	}
	pthread_create(&data->watcher, NULL, &watcher, data);
	i = -1;
	pthread_join(data->watcher, NULL);
	while (++i < data->count)
		pthread_join(data->philo[i].thread, NULL);
}