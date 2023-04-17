/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 18:26:54 by lsordo            #+#    #+#             */
/*   Updated: 2023/04/17 18:27:38 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	helpcheck_guys1(t_data *d)
{
	pthread_mutex_lock(&d->lock);
	d->done = 1;
	pthread_mutex_unlock(&d->lock);
}

void	helpcheck_guys2(t_data *d)
{
	int	i;
	int	t;
	int	f;

	i = 0;
	t = 0;
	f = 0;
	while (i < d->n_phi)
	{
		pthread_mutex_lock(&d->lock);
		t = d->philo[i].t_last;
		f = d->philo[i].finished;
		pthread_mutex_unlock(&d->lock);
		if (ft_clock(d->t_start) - t >= d->t_die && !f)
		{
			ft_print(&d->philo[i], "died");
			pthread_mutex_lock(&d->lock);
			d->stop = 1;
			pthread_mutex_unlock(&d->lock);
			break ;
		}
		i++;
	}
}

void	check_guys(t_data *d)
{
	int	i;
	int	all_finished;
	int	finished;

	i = 0;
	all_finished = 1;
	while (i < d->n_phi)
	{
		pthread_mutex_lock(&d->lock);
		finished = d->philo[i].finished;
		pthread_mutex_unlock(&d->lock);
		if (!finished)
		{
			all_finished = 0;
			break ;
		}
		i++;
	}
	if (all_finished)
		helpcheck_guys1(d);
	else
		helpcheck_guys2(d);
}
