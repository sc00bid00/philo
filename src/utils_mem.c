/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 08:42:19 by lsordo            #+#    #+#             */
/*   Updated: 2023/04/11 16:46:28 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	mutex_init(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		pthread_mutex_init(data->forks[i], NULL);
		i++;
	}
}

void	mutex_destroy(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		pthread_mutex_destroy(data->forks[i]);
		i++;
	}

}

void	philo_init(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		data->philo[i] = malloc(sizeof(t_philo));
		data->forks[i] = malloc(sizeof(pthread_mutex_t));
		data->philo[i]->id = i + 1;
		if (data->n_philo % 2 && i == data->n_philo - 1)
			data->philo[i]->shift = 2;
		else if (data->n_philo % 2)
			data->philo[i]->shift = 1;
		else
			data->philo[i]->shift = 2;
		if (data->philo[i]->shift == 1)
			data->philo[i]->doing |= EATING;
		else
			data->philo[i]->doing |= THINKING;
		data->philo[i]->lfork = i;
		if (i + 1 < data->n_lunch)
			data->philo[i]->rfork = i + 1;
		else
			data->philo[i]->rfork = 0;
		i++;
	}
}

void	data_init(t_data *data, char **argv)
{
	data->n_philo = ft_atoi(argv[1]);
	data->t_die = (useconds_t)ft_atoi(argv[2]);
	data->t_eat = (useconds_t)ft_atoi(argv[3]);
	data->t_sleep = (useconds_t)ft_atoi(argv[4]);
	if (argv[5])
		data->n_lunch = ft_atoi(argv[5]);
	else
		data->n_lunch = 0;
	data->philo = malloc(data->n_philo * sizeof(t_philo *));
	data->forks = malloc(data->n_philo * sizeof(pthread_mutex_t *));
	philo_init(data);
}

void	data_cleanup(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		free(data->philo[i]);
		free(data->forks[i]);
		i++;
	}
	free(data->philo);
	free(data->forks);
	free(data);
}
