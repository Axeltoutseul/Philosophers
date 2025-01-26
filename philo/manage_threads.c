/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 17:10:58 by axbaudri          #+#    #+#             */
/*   Updated: 2025/01/21 18:49:24 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	start_threads(t_main *main)
{
	long	i;

	i = 0;
	pthread_create(&main->monitor, NULL, &monitoring, main);
	while (i < (long)main->philo_nb)
	{
		pthread_create(&main->philosophers[i].thread, NULL,
			&ft_routine, (void *)&main->philosophers[i]);
		i++;
	}
	i = 0;
}

void	init_mutexes(t_main *main)
{
	pthread_mutex_init(&main->is_dead_mutex, NULL);
	pthread_mutex_init(&main->n_of_meals_mutex, NULL);
	pthread_mutex_init(&main->write_mutex, NULL);
	pthread_mutex_init(&main->end_mutex, NULL);
}
