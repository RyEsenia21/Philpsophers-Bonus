/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_life.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryesenia <ryesenia@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 20:11:32 by ryesenia          #+#    #+#             */
/*   Updated: 2022/04/18 19:16:35 by ryesenia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_forkc(t_philo *philo)
{
	int	i;
	int	curr;
	int	next;

	curr = philo->num;
	next = (curr + 1) % philo->argument->number_of_philosophers;
	i = 0;
	pthread_mutex_lock(&philo->argument->mutex);
	if (philo->argument->forks[curr] == 0
		&& philo->argument->forks[next] == 0)
	{
		print_take_forkcs(philo);
		philo->argument->forks[curr] = 1;
		philo->argument->forks[next] = 1;
		philo->count_eat++;
		i = 1;
	}
	pthread_mutex_unlock(&philo->argument->mutex);
	return (i);
}

void	*life_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	while (100)
	{
		while (100)
		{
			if (check_forkc(philo) == 1)
				break ;
		}
		func_eat(philo);
		if (philo->is_dead == 1)
			break ;
		func_think(philo);
		if (philo->is_dead == 1)
			break ;
		func_sleep(philo);
	}
	return (philo);
}
/* 
** Во время вывода времени, мы делаем следующее: от времени со старта программы 
** glotime мы вычетаем текущее время на данный момент 
** time_eat (это текущее время в которое он ест)
*/

void	func_eat(t_philo *philo)
{
	long long		time_eat;
	int				curr;
	int				next;

	curr = philo->num;
	next = (curr + 1) % philo->argument->number_of_philosophers;
	gettimeofday(&philo->must_eat, NULL);
	time_eat = get_u_sec(philo->must_eat);
	printf("%lld %d is eating\n", time_diff
		(get_u_sec(philo->argument->glotime), time_eat), philo->num + 1);
	smart_sleep(philo->argument->time_to_eat);
	philo->it_eat = 1;
	pthread_mutex_lock(&philo->argument->mutex);
	philo->argument->forks[curr] = 0;
	philo->argument->forks[next] = 0;
	pthread_mutex_unlock(&philo->argument->mutex);
}

void	func_think(t_philo *philo)
{
	struct timeval	think;
	long int		time_think;

	gettimeofday(&think, NULL);
	time_think = get_u_sec(think);
	printf("%lld %d is thinking\n", time_diff
		(get_u_sec(philo->argument->glotime), time_think), philo->num + 1);
}

void	func_sleep(t_philo *philo)
{
	struct timeval	sleep;
	long int		time_sleep;

	gettimeofday(&sleep, NULL);
	time_sleep = get_u_sec(sleep);
	printf("%lld %d is slepping\n", time_diff
		(get_u_sec(philo->argument->glotime), time_sleep), philo->num + 1);
	usleep(philo->argument->time_to_sleep);
}
