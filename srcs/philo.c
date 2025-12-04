/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 12:49:15 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/12/04 16:54:31 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	show_usage_error(void)
{
	ft_putstr_fd("====================================================\n", 2);
	ft_putstr_fd("                 PHILOSOPHERS ERROR              \n", 2);
	ft_putstr_fd("====================================================\n\n", 2);
	ft_putstr_fd("Incorrect number of arguments !!!\n", 2);
	ft_putstr_fd("The simulation requires the following format:\n\n", 2);
	ft_putstr_fd("./philo <nb_philos> <tt_die> <tt_eat> \n", 2);
	ft_putstr_fd("        <tt_sleep> [meals_count]\n\n ", 2);
	ft_putstr_fd("Example: ./philo 5 800 200 200 7\n\n", 2);
	ft_putstr_fd("Description:\n", 2);
	ft_putstr_fd(" - nb_philos: how many philos sit at the table\n", 2);
	ft_putstr_fd(" - tt_die (ms): max time a philo can go without eating\n", 2);
	ft_putstr_fd(" - tt_eat (ms): time spent eating\n", 2);
	ft_putstr_fd(" - tt_sleep (ms): time spent sleeping\n", 2);
	ft_putstr_fd(" - meals_count: stop when all philos ate this many times\n\n", 2);
	ft_putstr_fd("====================================================\n", 2);
	ft_putstr_fd("            Simulation aborted. Try again.\n", 2);
	ft_putstr_fd("====================================================\n", 2);
}

int	main(int ac, char **av)
{
	t_sim	sim;
	int		i;

	sim.start_sim = current_time_ms() + 500;
	if (ac != 5 && ac != 6)
		return (show_usage_error(), 1);
	if (!validate_args(ac, av, &sim))
		return (1);
	init_simulation(&sim);
	i = 0;
	while (i < sim.philo_count)
		pthread_join(sim.philos[i++].thread_id, NULL);
	pthread_join(sim.death_monitor, NULL); 
	pthread_mutex_destroy(&sim.death_lock); 
	pthread_mutex_destroy(&sim.print_lock); 
	i = 0;
	while (i < sim.philo_count)
	{
		pthread_mutex_destroy(&sim.philos[i].last_meal); 
		pthread_mutex_destroy(&sim.philos[i].meal_count); 
		pthread_mutex_destroy(&sim.forks[i++]); 
	}
	free(sim.philos);
	free(sim.forks);
	return (0);
}
