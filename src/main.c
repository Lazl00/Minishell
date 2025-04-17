/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcournoy <lcournoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 16:48:31 by lcournoy          #+#    #+#             */
/*   Updated: 2025/04/17 14:41:56 by lcournoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_data	init_data(char **env)
{
	t_data	data;
	
	data.env = env;
	data.tokens = NULL;
	data.fd[0] = -1;
	data.fd[1] = -1;
	data.path = get_path(data.env);
	
	return (data);
}

int		main(int argc, char **argv, char **env)
{
	char	*line;
	t_data	data;
	int		ignore;

	(void)argc;
	(void)argv;
	ignore = 0;	
	data = init_data(env);
	while (1)
	{
		printf("\n");
		line = readline("minishell 👅👀>  ");
		if (line == NULL)
		{
			printf("exit");
			break ;
		}
		add_history(line);
		parse_command(data, line);
		free(line);
	}
	exit(EXIT_FAILURE);
}
