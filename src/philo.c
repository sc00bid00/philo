/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 09:23:07 by lsordo            #+#    #+#             */
/*   Updated: 2023/04/11 13:23:39 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	*routine(void *data)
{
	(void)data;
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_data	*data;
	int		i;

	data = malloc(sizeof(t_data));
	if (argc > 7 || argc < 6)
	{
		printf("Wrong arguments - usage:\nnumber_of_philosophers\n\
time_to_die   [ms]\ntime_to_eat   [ms]\ntime_to_sleep [ms]\n\
[number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	data_init(data, argv);
	forks_init(data);
	i = 0;
	while (i < data->n_philo)
	{
		pthread_create((void *)data->philo[i], NULL, &routine, (void *)data);
		i++;
	}
	forks_destroy(data);
	data_cleanup(data);
	return (0);
}
