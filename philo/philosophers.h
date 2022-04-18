/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryesenia <ryesenia@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 19:17:05 by ryesenia          #+#    #+#             */
/*   Updated: 2022/04/13 20:42:03 by ryesenia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo	t_philo;
typedef struct s_data
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	int				*forks;
	struct timeval	glotime;
	t_philo			*arr_philo;
	pthread_t		*threads;
	pthread_mutex_t	mutex;
}				t_data;

/* 
** В структуре ниже, мы создаем философа с уникальным номером, но общим столом
** t_data *table
*/
typedef struct s_philo
{
	int				num;
	t_data			*argument;
	struct timeval	must_eat;
	int				is_dead;
	int				it_eat;
	int				count_eat;
}				t_philo;

int			check_argv(int argc, char *argv[]);
int			check_int(char *str);
int			ft_atoi(const char *str);
void		*life_philo(void *arg);
void		func_eat(t_philo *philo);
int			count_argv1(t_data *argument);
void		func_think(t_philo *philo);
void		func_sleep(t_philo *philo);
int			join_traeds(t_data *argument);
long long	timestamp(void);
void		smart_sleep(long long time);
long long	time_diff(long long past, long long pres);
void		dead(t_data *argument);
void		time_is_dead(t_data *argument);
long long	get_u_sec(struct timeval t);
void		print_take_forkcs(t_philo *philo);
int			tufta_so_strokami(t_data *argument, int argc, char *argv[]);

#endif