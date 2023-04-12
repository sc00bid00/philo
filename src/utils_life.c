/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:59:53 by lsordo            #+#    #+#             */
/*   Updated: 2023/04/12 17:56:41 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	eat_help(t_philo *p)
{
	if (p->id % 2)
	{
		pthread_mutex_lock(&p->data->forks[p->lf]);
		pthread_mutex_lock(&p->data->lock);
		ft_print(ft_clock(p->data->t_start), p->id, "has taken a fork");
		pthread_mutex_unlock(&p->data->lock);
		pthread_mutex_lock(&p->data->forks[p->rf]);
		pthread_mutex_lock(&p->data->lock);
		ft_print(ft_clock(p->data->t_start), p->id, "has taken a fork");
		pthread_mutex_unlock(&p->data->lock);
	}
	else
	{
		pthread_mutex_lock(&p->data->forks[p->rf]);
		pthread_mutex_lock(&p->data->lock);
		ft_print(ft_clock(p->data->t_start), p->id, "has taken a fork");
		pthread_mutex_unlock(&p->data->lock);
		pthread_mutex_lock(&p->data->forks[p->lf]);
		pthread_mutex_lock(&p->data->lock);
		ft_print(ft_clock(p->data->t_start), p->id, "has taken a fork");
		pthread_mutex_unlock(&p->data->lock);
	}
}

void	eat(t_philo	*p)
{
	eat_help(p);
	p->t_last = ft_clock(p->data->t_start);
	pthread_mutex_lock(&p->data->lock);
	ft_print(p->t_last, p->id, "is eating");
	pthread_mutex_unlock(&p->data->lock);
	ft_wait(p->t_eat);
	if (p->id % 2)
	{
		pthread_mutex_unlock(&p->data->forks[p->lf]);
		pthread_mutex_unlock(&p->data->forks[p->rf]);
	}
	else
	{
		pthread_mutex_unlock(&p->data->forks[p->rf]);
		pthread_mutex_unlock(&p->data->forks[p->lf]);
	}
}

void	ft_sleep(t_philo *p)
{
	pthread_mutex_lock(&p->data->lock);
	ft_print(ft_clock(p->data->t_start), p->id, "is sleeping");
	pthread_mutex_unlock(&p->data->lock);
	ft_wait(p->t_slp);
}

void	think(t_philo *p)
{
	pthread_mutex_lock(&p->data->lock);
	ft_print(ft_clock(p->data->t_start), p->id, "is thinking");
	pthread_mutex_unlock(&p->data->lock);
}
