/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulysseclem <ulysseclem@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 15:28:02 by uclement          #+#    #+#             */
/*   Updated: 2023/09/26 21:39:14 by ulysseclem       ###   ########.fr       */
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
	return (0);
}
