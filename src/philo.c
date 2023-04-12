/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:16:20 by lsordo            #+#    #+#             */
/*   Updated: 2023/04/12 17:54:57 by lsordo           ###   ########.fr       */
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
			ft_print(ft_clock(d->t_start), d->philo[i].id, "died");
			pthread_mutex_lock(&d->lock);
			d->philo[i].alive = 0;
			pthread_mutex_unlock(&d->lock);
			d->stop = 1;
			break ;
		}
		i++;
	}
}

void	*function(void *arg)
{
	t_philo	*phi;

	phi = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&phi->data->lock);
		if (phi->data->stop)
			return(NULL);
		pthread_mutex_unlock(&phi->data->lock);
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
	init(&data, argv);
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
