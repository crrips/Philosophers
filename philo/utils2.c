/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apiloian <apiloian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 12:57:49 by apiloian          #+#    #+#             */
/*   Updated: 2023/06/21 20:18:36 by apiloian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(int i)
{
	static struct timeval	init;
	struct timeval			tv;

	if (i == 1)
		gettimeofday(&init, NULL);
	gettimeofday(&tv, NULL);
	tv.tv_sec = tv.tv_sec - init.tv_sec;
	tv.tv_usec = tv.tv_usec - init.tv_usec;
	return (tv.tv_usec / 1000 + tv.tv_sec * 1000);
}

void	ft_usleep(long ms)
{
	long	start;

	start = get_time(0);
	usleep (ms * 960);
	while ((get_time(0) - start) < ms)
		usleep(10);
}

int	digit_check(char *str)

{
	while (*str)
	{
		if (str[0] == '-')
			str++;
		while (*str == ' ')
			str++;
		if (*str < '0' || *str > '9')
			return (1);
		str++;
	}
	return (0);
}

void	norminetting(t_philo *philo, int *c)
{
	long	time;

	time = get_time(0);
	pthread_mutex_lock(&philo->data->mumutex);
	if (time - philo->time_to_die > \
		philo->last_eat)
	{
		pthread_mutex_lock(&philo->data->helper);
		philo->data->vsio = 1;
		pthread_mutex_unlock(&philo->data->helper);
		pthread_mutex_lock(&philo->data->mutex_print);
		printf("%ldms\t%d died\n", time, philo->i + 1);
		pthread_mutex_unlock(&philo->data->mutex_print);
	}
	pthread_mutex_unlock(&philo->data->mumutex);
	ultra_norm(philo, c);
}

void	ultra_norm(t_philo *philo, int *c)
{
	pthread_mutex_lock(&philo->data->mumutex);
	if (philo->data->philo->eat_count >= \
		philo->data->nbr_each_must_eat)
	{
		pthread_mutex_lock(&philo->data->helper);
		(*c)++;
		pthread_mutex_unlock(&philo->data->helper);
	}
	pthread_mutex_unlock(&philo->data->mumutex);
	pthread_mutex_lock(&philo->data->mumutex);
	if (philo->data->nbr_each_must_eat != 0 && *c == \
		philo->data->phil_count)
	{
		pthread_mutex_lock(&philo->data->helper);
		philo->data->vsio = 1;
		pthread_mutex_unlock(&philo->data->helper);
	}
	pthread_mutex_unlock(&philo->data->mumutex);
}
