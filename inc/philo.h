/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 15:23:55 by lsordo            #+#    #+#             */
/*   Updated: 2023/04/08 15:47:33 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
# include <pthread.h>

# define DEAD		0b000
# define EATING		0b001
# define SLEEPING	0b010
# define THINKING	0b100
# define NO_FORKS	0b00;
# define FORK_RIGHT	0b01;
# define FORK_LEFT	0b10;
# define BOTH_FORKS	0b11;

/* threads and mutexes missing in the structures yet */

typedef struct	s_fork
{
	int	state;
}		t_fork;

typedef struct	s_philo
{
	int		id;
	int		shift;
	int		state;
	double	lapsed_lunch;
	int		forks;
}			t_philo;


#endif
