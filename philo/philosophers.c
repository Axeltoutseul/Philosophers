/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:54:10 by axbaudri          #+#    #+#             */
/*   Updated: 2025/01/17 14:24:29 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_main	*init_main_struct(int argc, char **argv)
{
	t_main	*main_struct;

	main_struct = (t_main *)malloc(sizeof(t_main));
	if (!main_struct)
		return (NULL);
	main_struct->philo_nb = ft_atol(argv[0]);
	main_struct->t_die = ft_atol(argv[1]);
	main_struct->t_eat = ft_atol(argv[2]);
	main_struct->t_sleep = ft_atol(argv[3]);
	if (argc == 5)
		main_struct->times_must_eat = ft_atol(argv[4]);
	else
		main_struct->times_must_eat = -1;
	init_mutexes(main_struct);
	main_struct->start = get_current_time();
	main_struct->end = 0;
	main_struct->forks = init_forks(main_struct->philo_nb);
	main_struct->philosophers = init_philosophers(main_struct);
	return (main_struct);
}

t_philo	*init_philosophers(t_main *main)
{
	t_philo	*philo;
	size_t	i;

	i = 0;
	philo = (t_philo *)malloc(sizeof(t_philo) * main->philo_nb);
	if (!philo)
		return (NULL);
	while (i < (size_t)main->philo_nb)
	{
		philo[i].id = i + 1;
		philo[i].n_of_meals = 0;
		philo[i].last_meal = main->start;
		pthread_mutex_init(&philo[i].last_meal_mutex, NULL);
		philo[i].is_dead = 0;
		philo[i].main = main;
		left_and_right_forks(main, philo, i);
		i++;
	}
	return (philo);
}
