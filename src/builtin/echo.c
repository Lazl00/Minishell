/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcournoy <lcournoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 14:47:00 by lcournoy          #+#    #+#             */
/*   Updated: 2025/04/24 17:56:48 by lcournoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	display_echo(t_data data, char **av, int count)
{
	while (av[i])
	{
		if (av[i] == '-')
		{
			if (check_quote_state(av[i], i, "\""))
				write(1, av[i], 1);
			i++;
		}
	}
}

int	ft_echo(t_data data, char **av)
{
	int	i;

	i = 0;
	while (av[i])
		i++;
	i = 0;
	display_echo(data, av, i);
	return (0);
}
