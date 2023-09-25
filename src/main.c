/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 15:28:02 by uclement          #+#    #+#             */
/*   Updated: 2023/09/24 16:55:04 by uclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

void	eat(t_philo *philo)
{
	struct timeval	eat_start;

	gettimeofday(&eat_start, NULL);
	ft_usleep(philo->tteat);
	printf("%ld : Philo %d is eating\n",  get_current_time() - philo->start, philo->id);
}

void	ft_sleep(t_philo *philo)
{
	printf("Philo %d is sleeping\n", philo->id);
}

void	*routine(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)philo_ptr;
	pthread_mutex_lock(&philo->data->mutex);
	eat(philo);
	pthread_mutex_unlock(&philo->data->mutex);
	// ft_sleep(philo);
	return (NULL);
}

void	init_philo(t_philo	*philo, char **av, u_int64_t start_time)
{
	philo->count = ft_atoi(av[1]);
	philo->ttdie = (u_int64_t)ft_atoi(av[2]);
	philo->tteat = (u_int64_t)ft_atoi(av[3]);
	philo->ttsleep = (u_int64_t)ft_atoi(av[4]);
	philo->must_eat = ft_atoi(av[5]);
	philo->start = start_time;
}

void	init_data(t_data *data, char **av)
{

	data->count = ft_atoi(av[1]);
	data->ttdie = ft_atoi(av[2]);
	data->tteat = ft_atoi(av[3]);
	data->ttsleep = ft_atoi(av[4]);
	data->must_eat = ft_atoi(av[5]);
}


int	main(int ac, char **av)
{
	int			i;
	t_data		*data;
	t_philo		*philo;
	struct timeval	start;
	u_int64_t		start_time;

	gettimeofday(&start, NULL);
	start_time = start.tv_sec * 1000 + start.tv_usec / 1000;
	if (ac != 6)
		return (0);
	data = malloc(sizeof(t_data));
	init_data(data, av);
	i = 0;
	philo = malloc(sizeof(t_philo) * data->count);
	i = 0;
	pthread_mutex_init(&data->mutex, NULL);
	while (i < data->count)
	{
		philo[i].id = i;
		init_philo(&philo[i], av, start_time);
		philo[i].data = data;
		pthread_create(&philo[i].thread, NULL, &routine, &philo[i]);
		i++;
	}
	i = 0;
	while (i < data->count)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	pthread_mutex_destroy(&data->mutex);
	return (0);
}
