/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 15:28:02 by uclement          #+#    #+#             */
/*   Updated: 2023/09/27 17:41:27 by uclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"


int	main(int ac, char **av)
{
	t_data			*data;
	if (ac != 6)
		return (0);
	data = malloc(sizeof(t_data));
	init_all(data, av);
	threads_maker(data);
	threads_breaker(data);
	// free(forks);
	free(data->philo);
	free(data);
	return (0);
}
