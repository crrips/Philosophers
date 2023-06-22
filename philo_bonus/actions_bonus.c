/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apiloian <apiloian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 16:04:53 by apiloian          #+#    #+#             */
/*   Updated: 2023/06/21 20:24:44 by apiloian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	norminetting(t_philo *philo, int *c)
{
	long	time;

	time = get_time(0);
	if (time - philo->time_to_die > \
		philo->last_eat)
	{
		sem_wait(philo->data->helper);
		philo->data->vsio = 1;
		sem_post(philo->data->helper);
		sem_wait(philo->data->print);
		printf("%ldms\t%d died\n", time, philo->i + 1);
		exit(EXIT_FAILURE);
	}
	if (philo->data->philo->eat_count >= \
		philo->data->nbr_each_must_eat)
		(*c)++;
	if (philo->data->nbr_each_must_eat > 0 && *c == \
		philo->data->phil_count)
		philo->data->vsio = 1;
}

void	*ibolit(void *x)
{
	t_philo	*philo;
	int		c;

	philo = (t_philo *)x;
	c = 0;
	while (1)
	{
		norminetting(philo, &c);
		if (philo->data->vsio == 1)
			exit(EXIT_FAILURE);
	}
	return (NULL);
}

void	sleeping_thinking(t_philo *philo)
{
	sem_wait(philo->data->helper);
	philo->eat_count += 1;
	sem_post(philo->data->helper);
	if (philo->data->vsio)
		return ;
	sem_wait(philo->data->print);
	printf("%ldms\t%d is sleeping\n", get_time(0), philo->i + 1);
	sem_post(philo->data->print);
	ft_usleep(philo->time_to_sleep);
	if (philo->data->vsio)
		return ;
	sem_wait(philo->data->print);
	printf("%ldms\t%d is thinking\n", get_time(0), philo->i + 1);
	sem_post(philo->data->print);
}

void	forking_eating(t_philo *philo)
{
	sem_wait(philo->data->forks);
	sem_wait(philo->data->forks);
	if (philo->data->vsio)
		return ;
	sem_wait(philo->data->print);
	printf("%ldms\t%d has taken a fork\n", get_time(0), philo->i + 1);
	printf("%ldms\t%d has taken a fork\n", get_time(0), philo->i + 1);
	printf("%ldms\t%d is eating\n", get_time(0), philo->i + 1);
	sem_post(philo->data->print);
	sem_wait(philo->data->helper);
	philo->last_eat = get_time(0);
	sem_post(philo->data->helper);
	ft_usleep(philo->time_to_eat);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
	sleeping_thinking(philo);
}

void	*routine(void *x)
{
	t_philo	*philo;

	philo = (t_philo *)x;
	pthread_create(&philo->data->i_bolit, NULL, ibolit, philo);
	while (philo->data->vsio != 1 && philo->data->phil_count > 1)
		forking_eating(philo);
	pthread_join(philo->data->i_bolit, NULL);
	exit(0);
}
