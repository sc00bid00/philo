/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 08:42:19 by lsordo            #+#    #+#             */
/*   Updated: 2023/04/11 10:42:52 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	alloc(t_data *data)
{
	data->fork = malloc(data->n_philo * sizeof(t_fork));
	data->philo = malloc(data->n_lunch * sizeof(t_philo));
}

void	forks_init(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		pthread_mutex_init(&data->fork[i].mutex_fork, NULL);
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
}
