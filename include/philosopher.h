/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 15:28:29 by uclement          #+#    #+#             */
/*   Updated: 2023/09/24 16:48:59 by uclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <unistd.h>
# include <stdlib.h>
# include <inttypes.h>
# include "libft.h"
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_data {
	int				count;
	u_int64_t		ttdie;
	u_int64_t		tteat;
	u_int64_t		ttsleep;
	int				must_eat;
	u_int64_t		start;
	pthread_mutex_t	mutex;
}	t_data;


typedef struct s_philo {
	int				id;
	int				count;
	int				ttdie;
	int				tteat;
	int				ttsleep;
	int				must_eat;
	u_int64_t		start;
	pthread_t		thread;
	pthread_mutex_t	mutex_philo;
	t_data			*data;
}	t_philo;

#endif