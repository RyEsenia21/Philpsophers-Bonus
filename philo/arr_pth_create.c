/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_pth_create.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryesenia <ryesenia@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 19:22:47 by ryesenia          #+#    #+#             */
/*   Updated: 2022/04/13 20:27:28 by ryesenia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	count_argv1(t_data *argument)
{
	int	i;

	i = 0;
	while (i < argument->number_of_philosophers)
	{
		argument->arr_philo[i].num = i;
		argument->arr_philo[i].argument = argument;
		if (pthread_create(&argument->threads[i], NULL,
				life_philo, &argument->arr_philo[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	join_traeds(t_data *argument)
{
	int	i;

	i = 0;
	while (i < argument->number_of_philosophers)
	{
		if (pthread_join(argument->threads[i], NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}
/* 
** Здесь мы проверяем жив ли кто из философов, 
** если хотя бы 1 жив, мы продолжаем бесконеный цикл,
*/

int	check_dead_philo(t_data *argument)
{
	int	i;

	i = 0;
	while (i < argument->number_of_philosophers)
	{
		if (argument->arr_philo[i].is_dead == 0)
			return (0);
		i++;
	}
	return (1);
}

/*
** Как только пришло время умирать, то мы завершаем работу программы.
*/
void	dead(t_data *argument)
{
	while (100)
	{
		time_is_dead(argument);
		if (check_dead_philo(argument) == 1)
			break ;
	}
}

/*
** Функция которая проверяет, что бы время с последнего приема пищи
** не было больше установленного до смерти
** 89 строчка работает только тогда когда филосов еще не ел.
*/
void	time_is_dead(t_data *argument)
{
	int			i;
	long long	t;

	i = -1;
	while (++i < argument->number_of_philosophers)
	{
		if (argument->arr_philo[i].is_dead == 1)
			continue ;
		if (argument->arr_philo[i].it_eat == 1)
			t = time_diff(timestamp(),
					get_u_sec(argument->arr_philo[i].must_eat));
		else
			t = time_diff(timestamp(), get_u_sec(argument->glotime));
		if (argument->time_to_die < t
			|| (argument->arr_philo[i].count_eat
				>= argument->number_of_times_each_philosopher_must_eat
				&& argument->number_of_times_each_philosopher_must_eat != 0))
		{
			argument->arr_philo[i].is_dead = 1;
			pthread_detach(argument->threads[i]);
			printf("philo № = %d is dead\n", i + 1);
		}
	}	
}
