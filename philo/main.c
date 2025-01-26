/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:54:05 by axbaudri          #+#    #+#             */
/*   Updated: 2025/01/23 18:18:36 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Si t_die est inferieur a t_sleep, il meurt pendant son sommeil

void	*ft_routine(void *args)
{
	t_philo	*philo;
	t_main	*main;

	philo = (t_philo *)args;
	main = philo->main;
	if (philo->id % 2 == 0)
		ft_usleep(main->t_eat / 2, main);
	while (!is_someone_dead(main) && !everybody_ate_enough(main))
	{
		eating(main, philo);
		sleep_and_think(main, philo);
	}
	return (0);
}

void	display_message(t_main *main, int id, const char *str)
{
	pthread_mutex_lock(&main->write_mutex);
	pthread_mutex_lock(&main->end_mutex);
	if (!main->end)
		printf("%ld %d %s\n", get_current_time() - main->start, id, str);
	pthread_mutex_unlock(&main->end_mutex);
	pthread_mutex_unlock(&main->write_mutex);
}

void	get_dead(t_main *main, t_philo *philo)
{
	pthread_mutex_lock(&main->write_mutex);
	pthread_mutex_lock(&main->end_mutex);
	pthread_mutex_lock(&main->is_dead_mutex);
	philo->is_dead = 1;
	pthread_mutex_unlock(&main->is_dead_mutex);
	if (!everybody_ate_enough(main))
		printf("%ld %d died\n", get_current_time() - main->start, philo->id);
	main->end = 1;
	pthread_mutex_unlock(&main->end_mutex);
	pthread_mutex_unlock(&main->write_mutex);
}

int	main(int argc, char **argv)
{
	t_main	*main;
	int		i;

	if (!is_valid(argc - 1, argv + 1))
		check_argv(argc - 1, argv + 1);
	else
	{
		i = 0;
		main = init_main_struct(argc - 1, argv + 1);
		start_threads(main);
		while (i < main->philo_nb)
			pthread_join(main->philosophers[i++].thread, NULL);
		pthread_join(main->monitor, NULL);
		free_main_struct(main);
	}
	return (0);
}
