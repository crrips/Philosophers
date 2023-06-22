/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apiloian <apiloian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:41:32 by apiloian          #+#    #+#             */
/*   Updated: 2023/06/20 19:32:22 by apiloian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data
{
	pthread_t		*phil;
	pthread_t		i_bolit;
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	mumutex;
	pthread_mutex_t	helper;
	pthread_mutex_t	*forks;
	int				i;
	int				phil_count;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				nbr_each_must_eat;
	int				vsio;
	struct s_philo	*philo;
}		t_data;

typedef struct s_philo
{
	int				i;
	pthread_mutex_t	*fork_l;
	pthread_mutex_t	*fork_r;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			last_eat;
	int				eat_count;
	struct s_data	*data;
}		t_philo;

long	ft_atol(const char *str);
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s);
char	**ft_split(char const *s, char c);

void	init(t_data *data);

void	*routine(void *x);

long	get_time(int i);

int		digit_check(char *str);

int		parse(int argc, char **argv, t_data *data);

void	ft_usleep(long ms);

void	*ibolit(void *x);

void	norminetting(t_philo *philo, int *c);

void	ultra_norm(t_philo *philo, int *c);

#endif