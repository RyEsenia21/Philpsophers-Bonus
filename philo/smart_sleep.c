/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smart_sleep.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryesenia <ryesenia@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 19:41:37 by ryesenia          #+#    #+#             */
/*   Updated: 2022/04/11 19:49:54 by ryesenia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
** Функции которые возвращают время прошедшее с 
** начала работы программы
*/
long long	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (get_u_sec(t));
}

long long	time_diff(long long past, long long pres)
{
	return (pres - past);
}

void	smart_sleep(long long time)
{
	long long	i;

	i = timestamp();
	while (21)
	{
		if (time_diff(i, timestamp()) >= time)
			break ;
		usleep(60);
	}
}

/* 
** функция сравнивает время от начала работы программы
** до времени приема пищи.
*/
long long	get_u_sec(struct timeval t)
{
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}
