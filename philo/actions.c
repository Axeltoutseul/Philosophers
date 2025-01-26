/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:50:59 by axbaudri          #+#    #+#             */
/*   Updated: 2025/01/23 18:26:43 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	check_meal_count(t_main *main)
{
	if (everybody_ate_enough(main) && !is_someone_dead(main))
	{
		pthread_mutex_lock(&main->write_mutex);
		printf("%ld everybody has eaten enough\n",
			get_current_time() - main->start);
		pthread_mutex_lock(&main->end_mutex);
		main->end = 1;
		pthread_mutex_unlock(&main->end_mutex);
		pthread_mutex_unlock(&main->write_mutex);
	}
}

void	philo_alone(t_main *main, t_philo *philo)
{
	if (pthread_mutex_lock(philo->right_fork) != 0)
		ft_putstr_fd("Error ! Right fork lock failed.", 2);
	else
		display_message(philo->main, philo->id, "has taken a fork");
	ft_usleep(main->t_die, main);
	get_dead(main, philo);
	if (pthread_mutex_unlock(philo->right_fork) != 0)
		ft_putstr_fd("Error ! Right fork unlock failed.", 2);
}

void	eating(t_main *main, t_philo *philo)
{
	if (main->times_must_eat == -1
		|| (main->times_must_eat && philo->n_of_meals < main->times_must_eat))
	{	
		if (main->philo_nb == 1)
			philo_alone(main, philo);
		else
		{
			take_forks(philo);
			display_message(main, philo->id, "is eating");
			pthread_mutex_lock(&philo->last_meal_mutex);
			philo->last_meal = get_current_time();
			pthread_mutex_unlock(&philo->last_meal_mutex);
			pthread_mutex_lock(&main->n_of_meals_mutex);
			philo->n_of_meals++;
			pthread_mutex_unlock(&main->n_of_meals_mutex);
			check_meal_count(main);
			ft_usleep(main->t_eat, main);
			drop_forks(philo);
		}
	}
}

void	sleep_and_think(t_main *main, t_philo *philo)
{
	long	t_think;

	display_message(main, philo->id, "is sleeping");
	ft_usleep(main->t_sleep, main);
	display_message(main, philo->id, "is thinking");
	if (main->philo_nb % 2 == 1)
	{
		t_think = 1.1 * (main->t_eat - main->t_sleep) + 50;
		ft_usleep(t_think, main);
	}
}

//time_to_t = 1.1 * (time_to_e - time_to_s) + 50