/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:59:53 by lsordo            #+#    #+#             */
/*   Updated: 2023/04/19 16:13:47 by lsordo           ###   ########.fr       */
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
	int	n;

	eat_help(p);
	pthread_mutex_lock(&p->data->lock);
	n = p->data->n_lun;
	p->t_last = ft_clock(p->data->t_start);
	pthread_mutex_unlock(&p->data->lock);
	p->lunches++;
	if (n && p->lunches >= n)
		p->finished = 1;
	ft_print(p, "is eating");
	ft_wait(p->t_eat);
}

void	ft_sleep(t_philo *p)
{
	ft_print(p, "is sleeping");
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
	ft_wait(p->t_slp);
}

void	think(t_philo *phi)
{
	if (phi->id % 2)
		ft_wait(1);
	else
		ft_wait(6);
	if (phi->lunches > 0)
		ft_print(phi, "is thinking");
}
