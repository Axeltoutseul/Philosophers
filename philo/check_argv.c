/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 17:23:09 by axbaudri          #+#    #+#             */
/*   Updated: 2025/01/17 12:55:02 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_digit(char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[i])
	{
		j = 0;
		if (argv[i][j] == '-')
			j++;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	has_an_empty_string(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		if (ft_strlen(strs[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	only_valid_numbers(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (ft_atol(argv[i]) < 1 || ft_atol(argv[i]) > 2147483647)
			return (0);
		i++;
	}
	return (1);
}

int	is_valid(int argc, char **argv)
{
	if ((argc < 4 || argc > 5) || has_an_empty_string(argv) || !is_digit(argv)
		|| !only_valid_numbers(argv) || ft_atol(argv[0]) > 200
		|| ft_atol(argv[1]) < 60 || ft_atol(argv[2]) < 60
		|| ft_atol(argv[3]) < 60)
		return (0);
	return (1);
}

void	check_argv(int argc, char **argv)
{
	if ((argc < 4 || argc > 5))
		printf("You must have 4 or 5 arguments\n");
	else if (has_an_empty_string(argv))
		printf("You can't have an empty string\n");
	else if (!is_digit(argv))
		printf("You must only type digits\n");
	else if (!only_valid_numbers(argv))
		printf("All numbers must be positive integers\n");
	else if (ft_atol(argv[0]) > 200)
		printf("Philosophers can't be more than 200\n");
	else if (ft_atol(argv[1]) < 60 || ft_atol(argv[2]) < 60
		|| ft_atol(argv[3]) < 60)
		printf("each time parameter must be at 60 ms minimum\n");
}
