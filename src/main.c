/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 15:28:02 by uclement          #+#    #+#             */
/*   Updated: 2023/09/23 18:03:02 by uclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int mail = 0;

void	*routine()
{
	int i;

	i = 0;
	// pthread_mutex_lock(&mutex);
	while (i < 100000)
	{
		mail++;
		i++;
	}
	// pthread_mutex_unlock(&mutex);
	return (NULL);
}

int	main(int ac, char **av)
{
	int				i;
	t_data			data;

	data.count = ft_atoi(av[1]);
	(void)ac;
	// pthread_mutex_init(&mutex, NULL);
	i = 0;
	data.philo = malloc(sizeof(t_philo) * data.count);
	data.philo->id = 0;
	data.philo->next = NULL;
	while (i < data.count)
	{
		data.philo->id = i;
		pthread_create(&data.philo[i].thread, NULL, &routine, NULL);
		i++;
		// printf("Thread %d cree\n", i);
	}
	i = 0;
	while (i < data.count)
	{
		pthread_join(data.philo[i].thread, NULL);
		i++;
		// printf("Thread %d fini\n", i);
	}
	printf("%d \n", mail);
	// pthread_mutex_destroy(&mutex);
	return (0);
}
