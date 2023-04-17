/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 20:11:06 by lsordo            #+#    #+#             */
/*   Updated: 2023/04/17 13:02:10 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	ft_create(t_data *data)
{
	int	i;

	data->t_start = ft_clock(0);
	i = 0;
	while (i < data->n_phi)
	{
		data->philo[i].data = data;
		data->philo[i].t_last = 0;
		data->philo[i].lunches = 0;
		data->philo[i].finished = 0;
		data->philo[i].id = i + 1;
		data->philo[i].lf = i;
		if (i + 1 < data->n_phi)
			data->philo[i].rf = i + 1;
		else
			data->philo[i].rf = 0;
		data->philo[i].t_die = data->t_die;
		data->philo[i].t_eat = data->t_eat;
		data->philo[i].t_slp = data->t_slp;
		i++;
	}
}

void	ft_launch(t_data *d)
{
	int	i;

	i = 0;
	while (i < d->n_phi)
	{
		pthread_create(&d->thread[i], NULL, function, &d->philo[i]);
		i++;
	}
}

int	allocforks(t_data *data)
{
	data->forks = malloc(data->n_phi * sizeof(pthread_mutex_t));
	if (!data->forks)
		return (ERR_ALLOCATION);
	return (0);
}
