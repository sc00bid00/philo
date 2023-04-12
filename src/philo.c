/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:16:20 by lsordo            #+#    #+#             */
/*   Updated: 2023/04/12 19:05:58 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	check_guys(t_data *d)
{
	int				i;
	unsigned long	t;

	i = 0;
	while (i < d->n_phi)
	{
		pthread_mutex_lock(&d->lock);
		t = d->philo[i].t_last;
		pthread_mutex_unlock(&d->lock);
		if (ft_clock(d->t_start) - t > d->t_die)
		{
			ft_print(&d->philo[i], "died");
			pthread_mutex_lock(&d->lock);
			d->philo[i].alive = 0;
			d->stop = 1;
			pthread_mutex_unlock(&d->lock);
			break ;
		}
		i++;
	}
}

void	*function(void *arg)
{
	t_philo	*phi;
	int		chk;

	phi = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&phi->data->lock);
		chk = phi->data->stop;
		pthread_mutex_unlock(&phi->data->lock);
		if (chk)
			return(NULL);
		eat(phi);
		ft_sleep(phi);
		think(phi);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (ERR_ARGS);
	if (init(&data, argv))
		return (ERR_ARGS);
	data.thread = malloc(data.n_phi * sizeof(pthread_t));
	if (!data.thread)
		return (EXIT_FAILURE);
	data.philo = malloc(data.n_phi * sizeof(t_philo));
	if (!data.philo)
		return (EXIT_FAILURE);
	ft_create(&data);
	while (!data.stop)
		check_guys(&data);
	cleanup(&data);
	return (0);
}
