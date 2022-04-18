/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryesenia <ryesenia@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 19:06:38 by ryesenia          #+#    #+#             */
/*   Updated: 2022/04/13 20:52:35 by ryesenia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_take_forkcs(t_philo *philo)
{
	struct timeval	take;
	long int		time_take;

	gettimeofday(&take, NULL);
	time_take = get_u_sec(take);
	printf("%lld %d has taken a fork\n", time_diff
		(get_u_sec(philo->argument->glotime), time_take), philo->num + 1);
}

int	init_int(t_data *argument, int argc, char *argv[])
{
	argument->number_of_philosophers = ft_atoi(argv[1]);
	argument->time_to_die = ft_atoi(argv[2]);
	argument->time_to_eat = ft_atoi(argv[3]);
	argument->time_to_sleep = ft_atoi(argv[4]);
	pthread_mutex_init(&argument->mutex, NULL);
	if (argc == 6)
		argument->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		argument->number_of_times_each_philosopher_must_eat = 0;
	argument->forks = (int *)malloc(sizeof(int)
			* (argument->number_of_philosophers));
	memset(argument->forks, 0, sizeof(int)
		* (argument->number_of_philosophers));
	if (argument->forks == NULL)
		return (3);
	argument->arr_philo = (t_philo *)malloc(sizeof(t_philo)
			* (argument->number_of_philosophers));
	if (argument->arr_philo == NULL)
		return (3);
	memset(argument->arr_philo, 0, sizeof(t_philo)
		* (argument->number_of_philosophers));
	return (0);
}

int	if_his_1(t_data *argument)
{
	if (argument->number_of_philosophers <= 1
		|| argument->number_of_philosophers >= 200
		|| argument->time_to_die < 60
		|| argument->time_to_eat < 60
		|| argument->time_to_sleep < 60)
	{
		printf("sam durak! :))))");
		return (1);
	}
	return (0);
}

int	tufta_so_strokami(t_data *argument, int argc, char *argv[])
{
	if (argc < 5 || argc > 6)
	{
		printf("count argument`s NEVERNO\n");
		return (1);
	}
	if (check_argv (argc, argv) != 0)
	{
		printf("ERROR FUNCTION CHECK_ARGV\n");
		return (1);
	}
	if (init_int(argument, argc, argv) != 0)
	{
		printf("ERROR FUNCTION INIT_INT\n");
		return (1);
	}
	if (if_his_1(argument) == 1)
		return (1);
	argument->threads = (pthread_t *)malloc(sizeof(pthread_t)
			* (argument->number_of_philosophers));
	if (argument->threads == NULL)
		return (1);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data			argument;

	if (tufta_so_strokami(&argument, argc, argv) == 1)
		return (1);
	gettimeofday(&argument.glotime, NULL);
	if (count_argv1(&argument) != 0)
	{
		printf("ERROR CREATE TREADS\n");
		return (1);
	}
	dead(&argument);
	join_traeds(&argument);
	pthread_mutex_destroy(&argument.mutex);
	free(argument.forks);
	free(argument.arr_philo);
	free(argument.threads);
	return (0);
}
