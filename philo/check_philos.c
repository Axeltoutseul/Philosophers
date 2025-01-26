/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_philos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:52:10 by axbaudri          #+#    #+#             */
/*   Updated: 2025/01/23 16:21:34 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_someone_dead(t_main *main)
{
	int	i;

	i = 0;
	while (i < main->philo_nb)
	{
		pthread_mutex_lock(&main->is_dead_mutex);
		if (main->philosophers[i].is_dead == 1)
		{
			pthread_mutex_unlock(&main->is_dead_mutex);
			return (1);
		}
		pthread_mutex_unlock(&main->is_dead_mutex);
		i++;
	}
	return (0);
}

int	everybody_ate_enough(t_main *main)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (main->times_must_eat == -1)
		return (0);
	while (i < main->philo_nb)
	{
		pthread_mutex_lock(&main->n_of_meals_mutex);
		if (main->philosophers[i++].n_of_meals == main->times_must_eat)
			count++;
		pthread_mutex_unlock(&main->n_of_meals_mutex);
	}
	if (count < main->philo_nb)
		return (0);
	return (1);
}

void	check_meal_and_death(t_main *main)
{
	t_philo	*philo;
	int		i;

	i = 0;
	while (i < main->philo_nb)
	{
		philo = &main->philosophers[i];
		pthread_mutex_lock(&philo->last_meal_mutex);
		if (get_current_time() - philo->last_meal >= main->t_die
			&& !everybody_ate_enough(main))
		{
			get_dead(main, philo);
			pthread_mutex_unlock(&philo->last_meal_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->last_meal_mutex);
		i++;
	}
}

void	*monitoring(void *arg)
{
	t_main	*main;

	main = (t_main *)arg;
	while (!is_someone_dead(main) && !everybody_ate_enough(main))
	{
		check_meal_and_death(main);
		if (everybody_ate_enough(main))
			break ;
		ft_usleep(5, main);
	}
	return (0);
}

/*void	*monitoring(void *arg)
{
	int		i;
	t_main	*main;
	t_philo	*philo;

	main = (t_main *)arg;
	while (!is_someone_dead(main) && !everybody_ate_enough(main))
	{
		i = 0;
		while (i < main->philo_nb)
		{
			philo = &main->philosophers[i];
			pthread_mutex_lock(&philo->last_meal_mutex);
			if (get_current_time() - philo->last_meal >= main->t_die
				&& !everybody_ate_enough(main))
			{
				get_dead(main, philo);
				pthread_mutex_unlock(&philo->last_meal_mutex);
				break ;
			}
			pthread_mutex_unlock(&philo->last_meal_mutex);
			i++;
		}
		if (everybody_ate_enough(main))
			break ;
		ft_usleep(5, main);
	}
	return (0);
}*/
