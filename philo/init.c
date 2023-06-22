/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apiloian <apiloian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 14:34:33 by apiloian          #+#    #+#             */
/*   Updated: 2023/06/21 20:27:45 by apiloian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_mutex(t_data *data)
{
	int	i;
	int	p;

	i = 0;
	p = data->phil_count;
	while (p--)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->mutex_print, NULL);
	pthread_mutex_init(&data->mumutex, NULL);
	pthread_mutex_init(&data->helper, NULL);
}

t_philo	*init_philo(t_data *data)
{
	t_philo	*philo;

	philo = malloc((data->phil_count) * sizeof(t_philo));
	data->i = data->phil_count;
	while (data->i--)
	{
		philo[data->i].i = data->i;
		philo[data->i].time_to_die = data->time_to_die;
		philo[data->i].time_to_eat = data->time_to_eat;
		philo[data->i].time_to_sleep = data->time_to_sleep;
		philo[data->i].fork_l = &data->forks[data->i];
		philo[data->i].fork_r = \
			&data->forks[(data->i + 1) % data->phil_count];
		philo[data->i].eat_count = 0;
		philo[data->i].last_eat = -1;
		philo[data->i].data = data;
	}
	return (philo);
}

void	destroy_mutex(t_data *data)
{
	data->i = data->phil_count;
	while (data->i--)
	{
		pthread_mutex_destroy(&data->forks[data->i]);
	}
	pthread_mutex_destroy(&data->mutex_print);
	pthread_mutex_destroy(&data->mumutex);
	pthread_mutex_destroy(&data->helper);
}

void	init(t_data *data)
{
	data->phil = malloc(data->phil_count * sizeof(pthread_t));
	data->forks = malloc((data->phil_count) * sizeof(pthread_mutex_t));
	init_mutex(data);
	data->vsio = 0;
	data->philo = init_philo(data);
	data->i = data->phil_count;
	while (data->i--)
		pthread_create(&data->phil[data->i], NULL, \
			routine, &data->philo[data->i]);
	pthread_create(&data->i_bolit, NULL, ibolit, data->philo);
	pthread_join(data->i_bolit, NULL);
	data->i = data->phil_count;
	while (data->i--)
		pthread_join(data->phil[data->i], NULL);
	destroy_mutex(data);
}
