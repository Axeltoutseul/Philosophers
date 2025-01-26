/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:30:57 by axbaudri          #+#    #+#             */
/*   Updated: 2025/01/21 16:01:42 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_main_struct(t_main *main)
{
	int	i;

	i = 0;
	while (i < main->philo_nb)
	{
		pthread_mutex_destroy(&main->philosophers[i].last_meal_mutex);
		pthread_mutex_destroy(&main->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&main->is_dead_mutex);
	pthread_mutex_destroy(&main->write_mutex);
	pthread_mutex_destroy(&main->n_of_meals_mutex);
	pthread_mutex_destroy(&main->end_mutex);
	free(main->philosophers);
	free(main->forks);
	free(main);
}
