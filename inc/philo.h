/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 15:23:55 by lsordo            #+#    #+#             */
/*   Updated: 2023/04/19 16:29:33 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define ERR_ARGSNUM 1
# define ERR_ARGSTYPE 2
# define ERR_ARGNEG 3
# define ERR_NOPHILS 4
# define ERR_SOLITARY 5
# define ERR_ALLOCATION 6

# define T_SLOT 100

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
# include <pthread.h>
# include <philo.h>

typedef struct s_data
{
	int				n_phi;
	int				t_die;
	int				t_eat;
	int				t_slp;
	int				t_start;
	int				n_lun;
	int				stop;
	int				done;
	pthread_mutex_t	p_lock;
	pthread_mutex_t	lock;
	pthread_mutex_t	*forks;
	pthread_t		*thread;
	struct s_philo	*philo;
}					t_data;

typedef struct s_philo
{
	int		id;
	int		lf;
	int		rf;
	int		t_die;
	int		t_eat;
	int		t_slp;
	int		t_last;
	int		lunches;
	int		finished;
	int		n_lun;
	t_data	*data;
}			t_philo;

void	*function(void *arg);

/* === utils_generic === */
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
int		ft_clock(int t_start);
void	ft_wait(int t);
void	ft_print(t_philo *p, char *msg);

/* === utils_init === */
int		init(t_data *data, char **arr);
void	cleanup(t_data *data);
void	ft_create(t_data *data);
void	ft_launch(t_data *d);
int		allocforks(t_data *data);

/* === utils_life === */
void	eat(t_philo	*p);
void	ft_sleep(t_philo *p);
void	think(t_philo *p);

/* === utils_errormgt === */
int		error_mgt(int argc, char **arr);
void	err_msg(int err_num);

/* === utils_check === */
void	check_guys(t_data *d);

#endif
