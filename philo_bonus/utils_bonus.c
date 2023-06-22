/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apiloian <apiloian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:07:07 by apiloian          #+#    #+#             */
/*   Updated: 2023/06/21 14:28:12 by apiloian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	ft_atol(const char *str)
{
	int		sign;
	long	res;

	sign = 1;
	res = 0;
	while ((*str >= 9 && *str <= 13) || *str == ' ' || *str == '+')
	{
		if (*str == '+' && !(*str < '0' || *str > '9'))
			return (0);
		str++;
	}
	if (*str == '-')
	{
		sign *= -1;
		str++;
	}
	while (*str)
	{
		if ((*str < '0' || *str > '9'))
			return (res * sign);
		res = res * 10 + *str - '0';
		str++;
	}
	return (res * sign);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (*str != '\0')
	{
		str++;
		i++;
	}
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_str;
	int		i;

	if (!s1 || !s2)
		return (0);
	new_str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!new_str)
		return (0);
	i = 0;
	while (*s1)
	{
		new_str[i] = *s1;
		i++;
		s1++;
	}
	while (*s2)
	{
		new_str[i] = *s2;
		i++;
		s2++;
	}
	new_str[i] = 0;
	return (new_str);
}

char	*ft_strdup(const char *s)
{
	char	*src;
	char	*str;
	int		i;

	i = 0;
	src = (char *)s;
	str = malloc(ft_strlen(src) * sizeof(char) + 1);
	if (str == 0)
		return (0);
	while (src[i] != '\0')
	{
		str[i] = src[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
