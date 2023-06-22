/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apiloian <apiloian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 14:34:33 by apiloian          #+#    #+#             */
/*   Updated: 2023/06/21 14:28:20 by apiloian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_sem(t_data *data)
{
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/helper");
	data->forks = sem_open("/forks", O_CREAT, S_IRWXU, data->phil_count);
	data->print = sem_open("/print", O_CREAT, S_IRWXU, 1);
	data->helper = sem_open("/helper", O_CREAT, S_IRWXU, 1);
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
		philo[data->i].eat_count = 0;
		philo[data->i].last_eat = -1;
		philo[data->i].data = data;
	}
	return (philo);
}

void	destroy_sem(t_data *data)
{
	sem_close(data->forks);
	sem_close(data->print);
	sem_close(data->helper);
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/helper");
}

void	destroy(t_data *data)
{
	int	rv;
	int	i;

	i = data->phil_count;
	while (i--)
	{
		waitpid(-1, &rv, 0);
		if (WEXITSTATUS(rv) > 0)
		{
			i = data->phil_count;
			while (i--)
				kill(data->philo[i].pid, SIGKILL);
			break ;
		}
	}
}

void	init(t_data *data)
{
	init_sem(data);
	data->vsio = 0;
	data->philo = init_philo(data);
	data->i = data->phil_count;
	while (data->i--)
	{
		data->philo[data->i].pid = fork();
		if (data->philo[data->i].pid == 0)
			routine(&data->philo[data->i]);
	}
	destroy(data);
	destroy_sem(data);
}
