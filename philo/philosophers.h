/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:54:13 by axbaudri          #+#    #+#             */
/*   Updated: 2025/01/21 18:42:42 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_main
{
	long			philo_nb;
	long			t_die;
	long			t_eat;
	long			t_sleep;
	int				count_forks;
	long			times_must_eat;
	long			start;
	int				end;
	pthread_t		monitor;
	pthread_mutex_t	is_dead_mutex;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	n_of_meals_mutex;
	pthread_mutex_t	start_mutex;
	pthread_mutex_t	end_mutex;
	struct s_philo	*philosophers;
	pthread_mutex_t	*forks;
}	t_main;

typedef struct s_philo
{
	int				n_of_meals;
	int				is_dead;
	int				id;
	t_main			*main;
	pthread_t		thread;
	long			last_meal;
	pthread_mutex_t	last_meal_mutex;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}	t_philo;

void			check_argv(int argc, char **argv);
void			check_meal_count(t_main *main);
void			display_message(t_main *main, int id, const char *str);
void			drop_forks(t_philo *philo);
void			eating(t_main *main, t_philo *philo);
int				everybody_ate_enough(t_main *main);
void			free_main_struct(t_main *main);
void			free_philosophers(int philosophers, t_philo **philo);
long			ft_atol(const char *str);
void			ft_putstr_fd(const char *str, int fd);
void			*ft_routine(void *args);
int				ft_strlen(const char *str);
char			*ft_strdup(const char *src);
int				ft_usleep(size_t milliseconds, t_main *main);
long			get_current_time(void);
int				has_an_empty_string(char **strs);
pthread_mutex_t	*init_forks(int philosophers);
t_main			*init_main_struct(int argc, char **argv);
void			init_mutexes(t_main *main);
t_philo			*init_philosophers(t_main *main);
int				is_digit(char **str);
int				is_someone_dead(t_main *main);
int				is_valid(int argc, char **argv);
void			left_and_right_forks(t_main *main, t_philo *philo, int i);
void			*monitoring(void *arg);
void			*new_philosopher(void *argv);
int				only_valid_numbers(char **argv);
void			philo_alone(t_main *main, t_philo *philo);
void			sleep_and_think(t_main *main, t_philo *philo);
void			sleeping(t_main *main, t_philo *philo);
void			get_dead(t_main *main, t_philo *philo);
void			start_threads(t_main *main);
void			take_forks(t_philo *philo);
void			thinking(t_main *main, t_philo *philo);
void			*thread_function(void *argv);

#endif
