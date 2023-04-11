/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 09:23:07 by lsordo            #+#    #+#             */
/*   Updated: 2023/04/11 11:02:28 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	main(int argc, char **argv)
{
	t_data	*data;


	data = malloc(sizeof(t_data));
	if (argc > 7 || argc < 6)
	{
		printf("Wrong arguments - usage:\nnumber_of_philosophers\n\
time_to_die   [ms]\ntime_to_eat   [ms]\ntime_to_sleep [ms]\n\
[number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	data_init(data, argv);
	alloc(data);
	forks_init(data);
	return (0);
}
