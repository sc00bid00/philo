/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:16:20 by lsordo            #+#    #+#             */
/*   Updated: 2023/04/17 20:42:38 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	help_function(t_philo *phi, int *chk1, int *chk2, int *n)
{
	pthread_mutex_lock(&phi->data->lock);
	*chk1 = phi->data->stop;
	*chk2 = phi->data->done;
	*n = phi->data->n_phi;
	pthread_mutex_unlock(&phi->data->lock);
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
		help_function(phi, &chk1, &chk2, &n);
		if (!(n % 2) && phi->id % 2 && phi->lunches == 0)
			ft_wait(1);
		else if ((n % 2) && phi->id % n && phi->lunches == 0)
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
