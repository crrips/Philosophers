/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apiloian <apiloian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 14:11:57 by apiloian          #+#    #+#             */
/*   Updated: 2023/06/16 12:45:46 by apiloian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	*join(int argc, char **argv)
{
	int		i;
	char	*str;
	char	*tmp;

	i = 1;
	while (i < argc)
	{
		if (!argv[i] || !*argv[i])
			return (NULL);
		if (i == 1)
			str = ft_strdup(argv[i]);
		else
		{
			tmp = ft_strjoin(str, " ");
			free (str);
			str = ft_strjoin(tmp, argv[i]);
			free(tmp);
		}
		i++;
	}
	return (str);
}

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

int	split_count(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	if (i < 4)
		return (0);
	return (i);
}

int	err(t_data *data, int len)
{
	int	i;

	i = 0;
	if (data->phil_count <= 0)
		i++;
	if (data->time_to_die <= 0)
		i++;
	if (data->time_to_eat <= 0)
		i++;
	if (data->time_to_sleep <= 0)
		i++;
	if (len > 4 && data->nbr_each_must_eat <= 0)
		i++;
	if (i > 0 || len > 5)
		return (-1);
	return (0);
}

int	parse(int argc, char **argv, t_data *data)
{
	char	**spl;
	char	*tmp;
	int		len;

	tmp = join(argc, argv);
	if (!tmp)
		return (free(tmp), 1);
	if (digit_check(tmp))
		return (free(tmp), 2);
	spl = ft_split(tmp, ' ');
	if (!spl)
		return (free(tmp), free_arr(spl), 3);
	len = split_count(spl);
	if (!len)
		return (free(tmp), free_arr(spl), 4);
	data->phil_count = ft_atol(spl[0]);
	data->time_to_die = ft_atol(spl[1]);
	data->time_to_eat = ft_atol(spl[2]);
	data->time_to_sleep = ft_atol(spl[3]);
	if (len > 4)
		data->nbr_each_must_eat = ft_atol(spl[4]);
	if (err(data, len) == -1)
		return (5);
	return (free(tmp), free_arr(spl), 0);
}
