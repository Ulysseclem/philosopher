/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulysseclem <ulysseclem@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 21:29:33 by ulysseclem        #+#    #+#             */
/*   Updated: 2023/09/26 23:06:16 by ulysseclem       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"


int	check_death(t_data *data)
{
	pthread_mutex_lock(&data->dead_lock);
	if(data->dead == 1)
	{
		write(1, "BORDEL\n", 7);
		return (1);
	}
	pthread_mutex_unlock(&data->dead_lock);
	return (0);
}

int is_dead(t_data *data)
{
	int	i;

	pthread_mutex_lock(&data->dead_lock);
	i = 0;
	while (i < data->count)
	{
		if (((data->philo[i].lastmeal + data->ttdie) < get_current_time()))
		{
			printf("%ld %d died\n",  get_current_time() - data->philo[i].start, data->philo[i].id);
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
	int	i = 0;

	data = (t_data *)data_ptr;
	pthread_mutex_init(&data->dead_lock, NULL); // pourquoi ici ca mqrche 
	while (i < 3) // FAIRE LA FONCTION DE COMPTE DE BOUFFE
	{
		// ft_usleep(5);
		if ((is_dead(data) == 1))
		{
			write(1, "test", 4);
			exit(0);
		}
		i++;
	}
	return (data_ptr);
}

void	threads_breaker(t_data *data)
{
	int	i;

	i = 0;
	while (++i < data->count)
		pthread_mutex_destroy(&data->forks[i]);
	pthread_mutex_destroy(&data->dead_lock);
}

void	threads_maker(t_data *data)
{
	int	i;
	
	i = -1;
	pthread_create(&data->watcher, NULL, &watcher, &data); // changer la valeur d'envoi a philo et pas data
	while (++i < data->count)
		pthread_create(&data->philo[i].thread, NULL, &routine, &data->philo[i]);
	pthread_join(data->watcher, NULL);
	i = -1;
	while (++i < data->count)
		pthread_join(data->philo[i].thread, NULL);
}