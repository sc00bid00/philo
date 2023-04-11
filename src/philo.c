/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 09:23:07 by lsordo            #+#    #+#             */
/*   Updated: 2023/04/11 18:53:21 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>

# define N 4
# define THINK_TIME 3
# define EAT_TIME 3

typedef struct	s_data
{
	pthread_mutex_t	*m;
	pthread_t		*p;
	pthread_mutex_t	w;
	int				id;
}					t_data;

void	think(int id, t_data d)
{
	struct timeval	ti;
	useconds_t		t;

	pthread_mutex_lock(&d.w);
	gettimeofday(&ti, NULL);
	t = ti.tv_sec + ti.tv_usec / 1000;
	pthread_mutex_unlock(&d.w);
	printf("[%d] Philosopher %d is thinking\n", (int)t, id);
	sleep(THINK_TIME);
}

void	eat(int id, int	lf, int rf, t_data d)
{
	struct timeval	ti;
	useconds_t		t;

	pthread_mutex_lock(&d.w);
	gettimeofday(&ti, NULL);
	t = ti.tv_sec + ti.tv_usec / 1000;
	pthread_mutex_unlock(&d.w);
	pthread_mutex_lock(&d.m[lf]);
	pthread_mutex_lock(&d.m[rf]);
	printf("[%d] Philosopher %d is eating with forks %d and %d\n", (int)t, id, lf, rf);
	sleep(EAT_TIME);
	pthread_mutex_unlock(&d.m[lf]);
	pthread_mutex_unlock(&d.m[rf]);
}

void	*func(void *arg)
{
	t_data	d;
	int		id;
	int		lf;
	int		rf;

	d = *(t_data *)arg;
	id = d.id;
	lf = id;
	rf = (id + 1) % N;
	if (id % 2 && id + 1 != N)
	{
		eat(d.id + 1, lf, rf, d);
		think(d.id + 1, d);
	}
	else if(id + 1 == N || !(id % 2))
	{
		think(d.id + 1, d);
		eat(d.id + 1, lf, rf, d);
	}
	return (NULL);
}

int	main(void)
{
	t_data	d;

	d.m = malloc(N * sizeof(pthread_mutex_t));
	d.p = malloc(N * sizeof(pthread_t));
	d.id = 0;
	while (d.id < N)
	{
		pthread_mutex_init(&d.m[d.id], NULL);
		d.id++;
	}
	d.id = 0;
	while (d.id < N)
	{
		pthread_create(&d.p[d.id], NULL, func, &d);
		d.id++;
	}
	d.id = 0;
	while (d.id < N)
	{
		pthread_join(d.p[d.id], NULL);
		d.id++;
	}
	d.id = 0;
	while (d.id < N)
	{
		pthread_mutex_destroy(&d.m[d.id]);
		d.id++;
	}
		return (0);
	}
