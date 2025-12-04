/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dead.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 16:04:07 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/12/04 16:33:37 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	check_death(t_sim *sim)
{
	int			i;
	long long	current;

	i = -1;
	while (++i < sim->philo_count)
	{
		current = current_time_ms();
		pthread_mutex_lock(&sim->philos[i].last_meal);
		if (current - sim->philos[i].last_meal_time > sim->tt_die)
		{
			print_status(&sim->philos[i], "died", sim->start_sim);
			pthread_mutex_lock(&sim->death_lock);
			sim->someone_died = 1;
			pthread_mutex_unlock(&sim->philos[i].last_meal);
			return (0);
		}
		pthread_mutex_unlock(&sim->philos[i].last_meal);
	}
	return (1);
}

static int	check_meal_count(t_sim *sim)
{
	int	i;
	int	full;

	full = 0;
	i = -1;

	while (++i < sim->philo_count)
	{
		pthread_mutex_lock(&sim->philos[i].meal_count);

		if (sim->philos[i].meals_eaten >= sim->eat_count)
			full++;
		pthread_mutex_unlock(&sim->philos[i].meal_count);
	}
	if (full == sim->philo_count)
	{
		pthread_mutex_lock(&sim->print_lock);
		printf("Everyone ate required times!\n");
		return (1);
	}
	return (0);
}

void	*death_monitor(void *data)
{
	t_sim	*sim;

	sim = (t_sim *)data;
	while (1)
	{
        if (sim->eat_count && check_meal_count(sim))
		{
			pthread_mutex_lock(&sim->death_lock);
			sim->someone_died = 1;
			pthread_mutex_unlock(&sim->death_lock);
			pthread_mutex_unlock(&sim->print_lock);
			return (NULL);
		}
		if (!check_death(sim))
		{
			pthread_mutex_unlock(&sim->death_lock);
			return (NULL);
		}
		usleep(100);
	}
	return (NULL);
}
