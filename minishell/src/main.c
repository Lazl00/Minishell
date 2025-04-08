/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcournoy <lcournoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 16:48:31 by lcournoy          #+#    #+#             */
/*   Updated: 2025/04/08 16:09:03 by wailas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	char	*rl;

	while (1)
	{
		rl = readline("minishell 👅👀> ");
		if (rl == NULL)
		{
			printf("exit");
			break ;
		}
		add_history(rl);
		parse_command(rl);
		free(rl);
	}
	exit(EXIT_FAILURE);
}
