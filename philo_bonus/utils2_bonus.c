/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apiloian <apiloian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 12:57:49 by apiloian          #+#    #+#             */
/*   Updated: 2023/06/21 14:28:07 by apiloian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
		usleep(100);
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
