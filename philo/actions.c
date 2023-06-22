/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apiloian <apiloian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 16:04:53 by apiloian          #+#    #+#             */
/*   Updated: 2023/06/21 20:17:11 by apiloian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ibolit(void *x)
{
	t_philo	*philo;
	int		i;
	int		c;

	philo = (t_philo *)x;
	while (1)
	{
		i = philo->data->phil_count;
		c = 0;
		while (i--)
		{
			norminetting(philo + i, &c);
			if (philo->data->vsio == 1)
				return (NULL);
		}
	}
	return (NULL);
}

int	sleeping_thinking(t_philo *philo)
{	
	pthread_mutex_lock(&philo->data->helper);
	if (philo->data->vsio)
	{
		pthread_mutex_unlock(&philo->data->helper);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->helper);
	pthread_mutex_lock(&philo->data->mumutex);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->data->mumutex);
	pthread_mutex_lock(&philo->data->mutex_print);
	printf("%ldms\t%d is sleeping\n", get_time(0), philo->i + 1);
	pthread_mutex_unlock(&philo->data->mutex_print);
	ft_usleep(philo->time_to_sleep);
	pthread_mutex_lock(&philo->data->helper);
	if (philo->data->vsio)
	{
		pthread_mutex_unlock(&philo->data->helper);
		return (2);
	}
	pthread_mutex_unlock(&philo->data->helper);
	pthread_mutex_lock(&philo->data->mutex_print);
	printf("%ldms\t%d is thinking\n", get_time(0), philo->i + 1);
	pthread_mutex_unlock(&philo->data->mutex_print);
	return (0);
}

void	taking(t_philo *philo)
{
	if (philo->i % 2 == 0)
	{
		pthread_mutex_lock(philo->fork_r);
		pthread_mutex_lock(philo->fork_l);
	}
	else
	{
		pthread_mutex_lock(philo->fork_l);
		pthread_mutex_lock(philo->fork_r);
	}
}

int	forking_eating(t_philo *philo)
{
	taking(philo);
	pthread_mutex_lock(&philo->data->helper);
	if (philo->data->vsio)
	{
		pthread_mutex_unlock(&philo->data->helper);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->helper);
	pthread_mutex_lock(&philo->data->mutex_print);
	printf("%ldms\t%d has taken a fork\n", get_time(0), philo->i + 1);
	printf("%ldms\t%d has taken a fork\n", get_time(0), philo->i + 1);
	printf("%ldms\t%d is eating\n", get_time(0), philo->i + 1);
	pthread_mutex_unlock(&philo->data->mutex_print);
	pthread_mutex_lock(&philo->data->mumutex);
	philo->last_eat = get_time(0);
	pthread_mutex_unlock(&philo->data->mumutex);
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->fork_l);
	pthread_mutex_unlock(philo->fork_r);
	if (sleeping_thinking(philo))
		return (2);
	return (0);
}

void	*routine(void *x)
{
	t_philo	*philo;

	philo = (t_philo *)x;
	while (philo->data->phil_count > 1)
		if (forking_eating(philo))
			break ;
	return (NULL);
}
