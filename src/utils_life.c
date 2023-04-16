/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:59:53 by lsordo            #+#    #+#             */
/*   Updated: 2023/04/16 09:35:10 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	eat_help(t_philo *p)
{
	if (p->id % 2)
	{
		pthread_mutex_lock(&p->data->forks[p->lf]);
		ft_print(p, "has taken a fork");
		pthread_mutex_lock(&p->data->forks[p->rf]);
		ft_print(p, "has taken a fork");
	}
	else if (!(p->id % 2))
	{
		pthread_mutex_lock(&p->data->forks[p->rf]);
		ft_print(p, "has taken a fork");
		pthread_mutex_lock(&p->data->forks[p->lf]);
		ft_print(p, "has taken a fork");
	}
}

void	eat(t_philo	*p)
{
	eat_help(p);
	pthread_mutex_lock(&p->data->lock);
	p->t_last = ft_clock(p->data->t_start);
	p->lunches++;
	pthread_mutex_unlock(&p->data->lock);
	if (p->lunches > p->data->n_lun && p->data->n_lun)
	{
		pthread_mutex_lock(&p->data->lock);
		p->finished = 1;
		pthread_mutex_unlock(&p->data->lock);
	}
	ft_print(p, "is eating");
	ft_wait(p->t_eat);
	if (p->id % 2)
	{
		pthread_mutex_unlock(&p->data->forks[p->lf]);
		pthread_mutex_unlock(&p->data->forks[p->rf]);
	}
	else if (!(p->id % 2))
	{
		pthread_mutex_unlock(&p->data->forks[p->rf]);
		pthread_mutex_unlock(&p->data->forks[p->lf]);
	}
}

void	ft_sleep(t_philo *p)
{
	ft_print(p, "is sleeping");
	ft_wait(p->t_slp);
}

void	think(t_philo *p)
{
	usleep(T_THINK);
	ft_print(p, "is thinking");
}
