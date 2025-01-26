/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_forks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:36:45 by axbaudri          #+#    #+#             */
/*   Updated: 2025/01/23 18:03:55 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	take_forks(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if (philo->id % 2 == 1)
	{
		first_fork = philo->right_fork;
		second_fork = philo->left_fork;
	}
	else
	{
		first_fork = philo->left_fork;
		second_fork = philo->right_fork;
	}
	if (pthread_mutex_lock(first_fork) != 0)
		ft_putstr_fd("Error ! First fork lock failed.", 2);
	else
		display_message(philo->main, philo->id, "has taken a fork");
	if (pthread_mutex_lock(second_fork) != 0)
		ft_putstr_fd("Error ! Second fork lock failed.", 2);
	else
		display_message(philo->main, philo->id, "has taken a fork");
}

/*void	take_forks(t_philo *philo)
{
	if (pthread_mutex_lock(philo->left_fork) != 0)
		ft_putstr_fd("Error ! First fork lock failed.", 2);
	else
		display_message(philo->main, philo->id, "has taken a fork");
	if (pthread_mutex_lock(philo->right_fork) != 0)
		ft_putstr_fd("Error ! Second fork lock failed.", 2);
	else
		display_message(philo->main, philo->id, "has taken a fork");
}*/

void	drop_forks(t_philo *philo)
{
	if (philo->left_fork && pthread_mutex_unlock(philo->left_fork) != 0)
		ft_putstr_fd("Error ! Left fork unlock failed.", 2);
	if (pthread_mutex_unlock(philo->right_fork) != 0)
		ft_putstr_fd("Error ! Right fork unlock failed.", 2);
}

pthread_mutex_t	*init_forks(int philo_nb)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * philo_nb);
	i = 0;
	while (i < philo_nb)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	return (forks);
}

void	left_and_right_forks(t_main *main, t_philo *philo, int i)
{
	if (main->philo_nb == 1)
		philo[i].left_fork = NULL;
	else if (i == 0)
		philo[i].left_fork = &main->forks[main->philo_nb - 1];
	else
		philo[i].left_fork = &main->forks[i - 1];
	philo[i].right_fork = &main->forks[i];
}
