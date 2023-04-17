/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:16:20 by lsordo            #+#    #+#             */
/*   Updated: 2023/04/17 18:17:31 by lsordo           ###   ########.fr       */
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

void	*function(void *arg)
{
	t_philo	*phi;
	int		chk1;
	int		chk2;
	int		n;

	phi = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&phi->data->lock);
		chk1 = phi->data->stop;
		chk2 = phi->data->done;
		n = phi->data->n_phi;
		pthread_mutex_unlock(&phi->data->lock);
		if (!(n % 2) && phi->id % 2 && phi->lunches == 0)
			ft_wait(1);
		else if((n % 2) && phi->id % n && phi->lunches == 0)
			ft_wait(1);
		if (chk1)
			return (NULL);
		if (chk2)
		{
			ft_wait(phi->t_die);
			return (NULL);
		}
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

	ret = 0;
	ret = error_mgt(argc, argv);
	if (ret)
		return (err_msg(ret), ret);
	ret = init(&data, argv);
	if (ret)
		return (err_msg(ret), ret);
	data.thread = malloc(data.n_phi * sizeof(pthread_t));
	if (!data.thread)
		return (err_msg(ERR_ALLOCATION), ERR_ALLOCATION);
	data.philo = malloc(data.n_phi * sizeof(t_philo));
	if (!data.philo)
		return (err_msg(ERR_ALLOCATION), ERR_ALLOCATION);
	ft_create(&data);
	ft_launch(&data);
	while (!data.stop && !data.done)
		check_guys(&data);
	cleanup(&data);
	return (0);
}
