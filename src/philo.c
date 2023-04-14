/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:16:20 by lsordo            #+#    #+#             */
/*   Updated: 2023/04/14 20:10:14 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	helpcheck_guys1(t_data *d)
{
	pthread_mutex_lock(&d->lock);
	d->stop = 1;
	pthread_mutex_unlock(&d->lock);
}

void	helpcheck_guys2(t_data *d, int all_finished)
{
	int	i;
	int	t;

	i = 0;
	t = 0;
	while (i < d->n_phi)
	{
		pthread_mutex_lock(&d->lock);
		t = d->philo[i].t_last;
		pthread_mutex_unlock(&d->lock);
		if (ft_clock(d->t_start) - t > d->t_die && !all_finished)
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
		helpcheck_guys2(d, all_finished);
}

void	*function(void *arg)
{
	t_philo	*phi;
	int		chk;

	phi = (t_philo *)arg;
	while (1)
	{
		if (phi->id % 2 && phi->lunches == 0)
			ft_wait(3);
		if (phi->id % 3 && phi->lunches == 0)
			ft_wait(2);
		if (phi->id % 2 && phi->lunches == 0)
			ft_wait(1);
		pthread_mutex_lock(&phi->data->lock);
		chk = phi->data->stop;
		pthread_mutex_unlock(&phi->data->lock);
		if (chk)
			return (NULL);
		eat(phi);
		ft_sleep(phi);
		think(phi);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		ret;

	if (argc < 5 || argc > 6)
		return (ERR_ARGS);
	ret = init(&data, argv);
	if (ret)
		return (ret);
	data.thread = malloc(data.n_phi * sizeof(pthread_t));
	if (!data.thread)
		return (ERR_ALLOCATION);
	data.philo = malloc(data.n_phi * sizeof(t_philo));
	if (!data.philo)
		return (ERR_ALLOCATION);
	ft_create(&data);
	ft_launch(&data);
	while (!data.stop)
		check_guys(&data);
	cleanup(&data);
	return (0);
}
