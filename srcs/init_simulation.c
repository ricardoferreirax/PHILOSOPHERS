/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_simulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 15:59:25 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/12/04 16:33:42 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	init_philos(t_sim *sim, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < sim->philo_count)
	{
		pthread_mutex_init(&sim->forks[i], NULL);
		philos[i].philo_id = i + 1;
		philos[i].tt_eat = sim->tt_eat;
		philos[i].tt_sleep = sim->tt_sleep;
		philos[i].l_fork = &sim->forks[i];
		philos[i].r_fork = &sim->forks[(i + 1) % sim->philo_count];
		philos[i].start_sim = sim->start_sim;
		philos[i].last_meal_time = sim->start_sim;
		philos[i].table = sim;
		pthread_mutex_init(&philos[i].last_meal, NULL);
		pthread_mutex_init(&philos[i].meal_count, NULL);
		i++;
	}
}

void	init_simulation(t_sim *sim)
{
	t_philo	*philo_arr;
	int				i;

	pthread_mutex_init(&sim->print_lock, NULL);
	pthread_mutex_init(&sim->death_lock, NULL);
	sim->forks = malloc(sim->philo_count * sizeof(t_mutex));
	if (!sim->forks)
		return ;
	philo_arr = malloc(sim->philo_count * sizeof(t_philo));
	if (!philo_arr)
		return ;
	init_philos(sim, philo_arr);
	sim->philos = philo_arr;
	i = 0;
	while (i < sim->philo_count)
	{
		if (pthread_create(&philo_arr[i].thread_id, NULL,
				philo_routine, &philo_arr[i]))
		{
			sim->someone_died = 1;
			return ;
		}
		usleep(100);
		i++;
	}
	if (pthread_create(&sim->death_monitor, NULL, death_monitor, sim))
	{
		sim->someone_died = 1;
		return ;
	}
}
