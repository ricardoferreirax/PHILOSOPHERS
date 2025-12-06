/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 16:04:07 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/12/05 20:15:11 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	philo_has_died(t_sim *sim, int i)
{
	long long	current;

	current = current_time_ms();
	pthread_mutex_lock(&sim->philos[i].last_meal);
	if (current - sim->philos[i].last_meal_time >= sim->tt_die)
	{
		pthread_mutex_unlock(&sim->philos[i].last_meal);
		pthread_mutex_lock(&sim->death_lock);
		if (!sim->someone_died)
		{
			sim->someone_died = 1;
			pthread_mutex_lock(&sim->print_lock);
			printf("%lld %d died\n",
				current - sim->start_sim,
				sim->philos[i].philo_id);
			pthread_mutex_unlock(&sim->print_lock);
		}
		pthread_mutex_unlock(&sim->death_lock);

		return (0);
	}
	pthread_mutex_unlock(&sim->philos[i].last_meal);
	return (1);
}

static int	check_death(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->philo_count)
	{
		if (!philo_has_died(sim, i))
			return (0);
		i++;
	}
	return (1);
}

static int	count_full_philos(t_sim *sim)
{
	int	i;
	int	full;

	i = 0;
	full = 0;
	while (i < sim->philo_count)
	{
		pthread_mutex_lock(&sim->philos[i].meal_count);
		if (sim->philos[i].meals_eaten >= sim->eat_count)
			full++;
		pthread_mutex_unlock(&sim->philos[i].meal_count);
		i++;
	}
	return (full);
}

static int	check_meal_count(t_sim *sim)
{
	int	full;

	if (sim->eat_count == 0)
		return (0);
	full = count_full_philos(sim);
	if (full == sim->philo_count)
	{
		pthread_mutex_lock(&sim->print_lock);
		printf("Everyone ate required times!\n");
		pthread_mutex_unlock(&sim->print_lock);
		pthread_mutex_lock(&sim->death_lock);
		sim->someone_died = 1;
		pthread_mutex_unlock(&sim->death_lock);
		return (1);
	}
	return (0);
}

void	*death_monitor(void *data)
{
	t_sim *sim;

	sim = (t_sim *)data;
	while (1)
	{
		if (sim->eat_count != 0 && check_meal_count(sim))
			return (NULL);

		if (!check_death(sim))
			return (NULL);

		usleep(100);
	}
	return (NULL);
}
