/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:54:31 by lsordo            #+#    #+#             */
/*   Updated: 2023/04/19 16:22:39 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	safety_chk(t_data *d)
{
	if (!d->n_phi || !d->t_die || !d->t_eat || !d->t_slp)
		return (ERR_ARGSNUM);
	if (d->n_phi == 1)
	{
		printf("%d 1 has taken a fork\n", 0);
		ft_wait(d->t_die);
		printf("%d 1 died\n", d->t_die);
		return (ERR_SOLITARY);
	}
	return (0);
}

void	init_help(t_data *data, char **arr)
{
	(*data).stop = 0;
	(*data).done = 0;
	(*data).n_phi = ft_atoi(arr[1]);
	(*data).t_die = ft_atoi(arr[2]);
	(*data).t_eat = ft_atoi(arr[3]);
	(*data).t_slp = ft_atoi(arr[4]);
}

void	init_help2(t_data *data)
{
	int	i;

	pthread_mutex_init(&(*data).lock, NULL);
	pthread_mutex_init(&(*data).p_lock, NULL);
	i = 0;
	while (i < data->n_phi)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
}

int	init(t_data *data, char **arr)
{
	int	ret;

	init_help(data, arr);
	ret = safety_chk(data);
	if (ret)
		return (ret);
	if (arr && arr[5])
	{
		(*data).n_lun = ft_atoi(arr[5]);
		if (data->n_lun < 0)
			return (ERR_ARGSTYPE);
	}
	else if (!arr[5])
		(*data).n_lun = 0;
	ret = allocforks(data);
	if (ret)
		return (ret);
	init_help2(data);
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
	pthread_mutex_destroy(&data->p_lock);
	free(data->thread);
	free(data->philo);
	free(data->forks);
}
