/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulysseclem <ulysseclem@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 20:34:54 by ulysseclem        #+#    #+#             */
/*   Updated: 2023/09/26 22:37:14 by ulysseclem       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"




void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	printf("%ld %d has taken a fork\n",  get_current_time() - philo->start, philo->id);
	pthread_mutex_lock(philo->r_fork);
	printf("%ld %d has taken a fork\n",  get_current_time() - philo->start, philo->id);
	printf("%ld %d is eating\n",  get_current_time() - philo->start, philo->id);
	ft_usleep(philo->data->tteat);
	philo->lastmeal = get_current_time();
	philo->count_meal++;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	philo_sleep(t_philo *philo)
{
	printf("%ld %d is sleeping\n",  get_current_time() - philo->start, philo->id);
	ft_usleep(philo->data->ttsleep);
}

void	philo_think(t_philo *philo)
{
	printf("%ld %d is thinking\n",  get_current_time() - philo->start, philo->id);
	ft_usleep(1);
}


void	*routine(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)philo_ptr;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while(philo->data->must_eat > philo->count_meal && check_death(philo->data) != 1)
	{
		eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	exit(0);
	return (NULL);
}