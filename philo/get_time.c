/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:18:27 by axbaudri          #+#    #+#             */
/*   Updated: 2025/01/20 20:00:00 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_usleep(size_t milliseconds, t_main *main)
{
	size_t	start;

	start = get_current_time();
	while (get_current_time() - start < milliseconds && !is_someone_dead(main))
		usleep(100);
	return (0);
}

long	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) < 0)
		ft_putstr_fd("error gettimeofday()\n", 2);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
