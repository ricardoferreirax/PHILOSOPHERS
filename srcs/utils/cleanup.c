/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 21:17:39 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/01/02 12:26:31 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

static void	cleanup_simulation(t_sim *table, int code)
{
	int	i;

	i = 0;
	while (i < table->philo_count && code > 0)
	{
		pthread_mutex_destroy(&table->forks[i]);
		if (code > 3)
			pthread_mutex_destroy(&table->philos[i].last_meal);
		if (code > 4)
			pthread_mutex_destroy(&table->philos[i].meal_count);
		i++;
	}
	if (code > 0)
	{
		pthread_mutex_destroy(&table->print_lock);
		if (code > 1)
			pthread_mutex_destroy(&table->death_lock);
		if (code > 2)
			pthread_mutex_destroy(&table->full_lock);
		free(table->forks);
		free(table->philos);
	}
}

static void	cleanup_error_msg(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(2, &str[i], 1);
		i++;
	}
}

int	cleanup_and_error(t_sim *table, char *str, int code)
{
	cleanup_simulation(table, code);
	cleanup_error_msg(str);
	return (0);
}
