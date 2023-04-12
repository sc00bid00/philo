/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:54:31 by lsordo            #+#    #+#             */
/*   Updated: 2023/04/12 17:53:42 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	init(t_data *data, char **arr)
{
	int	i;

	(*data).stop = 0;
	(*data).n_phi = ft_atoi(arr[1]);
	(*data).t_die = ft_atoi(arr[2]);
	(*data).t_eat = ft_atoi(arr[3]);
	(*data).t_slp = ft_atoi(arr[4]);
	if (arr && arr[5])
		(*data).n_lun = ft_atoi(arr[5]);
	data->forks = malloc(data->n_phi * sizeof(pthread_mutex_t));
	if (!data->forks)
		exit(EXIT_FAILURE);
	i = 0;
	while (i < data->n_phi)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&(*data).lock, NULL);
}

void	cleanup(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_phi)
	{
		pthread_join(data->thread[i], NULL);
		i++;
	}
	i = 0;
	while (i < data->n_phi)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->lock);
	free(data->thread);
	free(data->philo);
	free(data->forks);
}

void	ft_create(t_data *data)
{
	int	i;

	data->t_start = ft_clock(0);
	i = 0;
	while (i < data->n_phi)
	{
		data->philo[i].data = data;
		data->philo[i].alive = 1;
		data->philo[i].t_last = 0;
		data->philo[i].id = i + 1;
		data->philo[i].lf = i;
		if (i + 1 < data->n_phi)
			data->philo[i].rf = i + 1;
		else
			data->philo[i].rf = 0;
		data->philo[i].t_die = data->t_die;
		data->philo[i].t_eat = data->t_eat;
		data->philo[i].t_slp = data->t_slp;
		pthread_create(&data->thread[i], NULL, function, &data->philo[i]);
		i++;
	}
}
