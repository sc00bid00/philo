/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 10:21:04 by lsordo            #+#    #+#             */
/*   Updated: 2023/04/11 10:55:21 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	tmp_prtarray(char **arr)
{
	int	i;

	i = 0;
	ft_putendl_fd("=== debug tmp_prtarray ===", 2);
	while (arr && arr[i])
	{
		ft_putnbr_fd(i, 2);
		ft_putchar_fd(' ', 2);
		ft_putendl_fd(arr[i], 2);
		i++;
	}
	ft_putendl_fd("=== debug tmp_prtarray ===", 2);
}

void	tmp_prtdata(t_data	*data)
{
	ft_putendl_fd("=== debug tmp_prtdata ===", 2);
	ft_putstr_fd("n_philo ", 2);
	ft_putnbr_fd(data->n_philo, 2);
	ft_putstr_fd("\nt_die ", 2);
	ft_putnbr_fd(data->t_die, 2);
	ft_putstr_fd("\nt_eat ", 2);
	ft_putnbr_fd(data->t_eat, 2);
	ft_putstr_fd("\nt_sleep ", 2);
	ft_putnbr_fd(data->t_sleep, 2);
	ft_putstr_fd("\nn_lunch ", 2);
	ft_putnbr_fd(data->n_lunch, 2);
	ft_putendl_fd("\n=== debug tmp_prtdata ===", 2);

}
