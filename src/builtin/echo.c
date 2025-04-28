/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcournoy <lcournoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 14:47:00 by lcournoy          #+#    #+#             */
/*   Updated: 2025/04/28 12:38:27 by wailas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	display_echo(char *av)
{
	int	back_slash;
	int	i;

	i = 0;
	back_slash = 0;
	while (av[i])
	{
		if (ft_strcmp(av, "-n"))
			back_slash = 1;
		write(1, &av[i], 1);
		i++;
	}
	if (back_slash == 0)
		write(1, "\n", 1);
}

int	ft_echo(char *av)
{
	int	i;

	i = 0;
	while (av[i])
		i++;
	i = 0;
	display_echo(av);
	return (0);
}
