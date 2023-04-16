/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_errormgt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 14:51:25 by lsordo            #+#    #+#             */
/*   Updated: 2023/04/16 15:08:20 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	err_msg(int err_num)
{
	if (err_num == 1)
		write(2, "error: expected between 4 and 5 numeric arguments\n", 51);
	else if (err_num == 2)
		write(2, "error: expected numeric arguments only\n", 40);
	else if (err_num == 3)
		write(2, "error: expected positive numbers only\n", 39);
	else if (err_num == 4)
		write(2, "error: at least 1 philospher expected\n", 39);
	else if (err_num == 6)
		write(2, "erorr: malloc defaulted\n", 25);
}

int	error_mgt(int argc, char **arr)
{
	int	i;
	int	j;

	if (argc < 5 || argc > 6)
		return (ERR_ARGSNUM);
	i = 1;
	while (arr && arr[i])
	{
		if (ft_atoi(arr[i]) < 0)
			return (ERR_ARGNEG);
		j = 0;
		while (arr[i][j])
		{
			if (!ft_isdigit(arr[i][j]))
				return (ERR_ARGSTYPE);
			j++;
		}
		if (ft_atoi(arr[1]) == 0)
			return (ERR_NOPHILS);
		i++;
	}
	return (0);
}
