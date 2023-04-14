/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:54:31 by lsordo            #+#    #+#             */
/*   Updated: 2023/04/14 14:50:00 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	safety_chk(t_data *d)
{
	if (!d->n_phi || !d->t_die || !d->t_eat || !d->t_slp)
		return (ERR_ARGS);
	if (d->n_phi == 1)
	{
		printf("%d\t1\thas taken a fork\n", 0);
		ft_wait(d->t_die);
		printf("%lu\t1\tdied\n", d->t_die);
		return (ERR_SOLITARY);
	}
	return (0);
}

void	init_help(t_data *data, char **arr)
{
	(*data).stop = 0;
	(*data).n_phi = ft_atoi(arr[1]);
	(*data).t_die = ft_atoi(arr[2]);
	(*data).t_eat = ft_atoi(arr[3]);
	(*data).t_slp = ft_atoi(arr[4]);
}

int	init(t_data *data, char **arr)
{
	int	i;
	int ret;

	init_help(data, arr);
	ret = safety_chk(data);
	if (ret)
		return (ret);
	if (arr && arr[5])
	{
		(*data).n_lun = ft_atoi(arr[5]);
		if (!data->n_lun)
			return (ERR_ARGS);
	}
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
	return (0);
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
		pthread_create(&data->thread[i], NULL, function, &data->philo[i]);
		i++;
	}
}
