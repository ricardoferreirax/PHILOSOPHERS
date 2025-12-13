/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 12:49:15 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/12/13 16:23:07 by rmedeiro         ###   ########.fr       */
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

int	validate_args(int ac, char **av, t_sim *sim)
{
	if (!validate_numbers(ac, av))
		return (0);
	sim->philo_count = ft_atoi(av[1]);
	sim->tt_die = ft_atoi(av[2]);
	sim->tt_eat = ft_atoi(av[3]);
	sim->tt_sleep = ft_atoi(av[4]);
	sim->eat_count = 0;
	if (ac == 6)
		sim->eat_count = ft_atoi(av[5]);
	sim->someone_died = 0;
	return (1);
}

int	main(int ac, char **av)
{
	t_sim	sim;

	sim.start_sim = current_time_ms();
	if (ac != 5 && ac != 6)
		return (show_usage_error(), 1);
	if (!validate_args(ac, av, &sim))
		return (1);
	if (!init_simulation(&sim))
		return (1);
	cleanup_simulation(&sim, sim.philo_count);
	return (0);
}
