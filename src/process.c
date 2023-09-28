/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 20:34:54 by ulysseclem        #+#    #+#             */
/*   Updated: 2023/09/28 17:58:25 by uclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"


void	print_txt(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->data->print);
	printf("%ld %d %s\n", get_current_time() - philo->start, philo->id, str);
	pthread_mutex_unlock(&philo->data->print);
}

void	eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->r_fork);
		if (loop_death(philo) == 0)
			print_txt(philo, "has taken a fork");
		pthread_mutex_lock(philo->l_fork);
		if (loop_death(philo) == 0)
			print_txt(philo, "has taken a fork");
	}
	else 
	{
		pthread_mutex_lock(philo->l_fork);
		if (loop_death(philo) == 0)
			print_txt(philo, "has taken a fork");
		pthread_mutex_lock(philo->r_fork);
		if (loop_death(philo) == 0)
			print_txt(philo, "has taken a fork");
	}
	if (loop_death(philo) == 0)
		print_txt(philo, "is eating");
	pthread_mutex_lock(&philo->test);
	philo->is_eating = 1;
	philo->lastmeal = get_current_time();
	philo->count_meal++;
	pthread_mutex_unlock(&philo->test);
	// philo->is_eating = 0;
	ft_usleep(philo->data->tteat);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);

}

void	philo_sleep(t_philo *philo)
{
	print_txt(philo, "is sleeping");
	ft_usleep(philo->data->ttsleep);
}

void	philo_think(t_philo *philo)
{
	print_txt(philo, "is thinking");
	ft_usleep(1);
}


void	*routine(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)philo_ptr;
	// if (philo->id % 2 == 0)
	// 	ft_usleep(1);
	//  while(philo->must_eat > philo->count_meal && check_death(philo) != 1)
	while(philo->must_eat > philo->count_meal && loop_death(philo) == 0)
	{
		if (loop_death(philo) == 0)
			eat(philo);
		if (loop_death(philo) == 0)
			philo_sleep(philo);
		if (loop_death(philo) == 0)
			philo_think(philo);
	}
	return (NULL);
}