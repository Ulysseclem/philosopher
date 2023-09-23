/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 15:28:29 by uclement          #+#    #+#             */
/*   Updated: 2023/09/23 17:41:34 by uclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSPHER_H

# include <unistd.h>
# include <stdlib.h>
# include <inttypes.h>
# include "libft.h"
# include <pthread.h>
# include <stdio.h>

typedef struct s_philo {
	int				id;
	struct t_philo	*next;
	pthread_t		thread;
}	t_philo;

typedef struct s_data {
	// pthread_mutex_t	mutex;
	int			count;
	t_philo		*philo;
}	t_data;

#endif