/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcournoy <lcournoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 16:48:31 by lcournoy          #+#    #+#             */
/*   Updated: 2025/05/06 16:07:22 by lcournoy         ###   ########.fr       */
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

int	main(int argc, char **argv, char **env)
{
	char			*line;
	t_data			data;
	int				ignore;
	t_token_node	*tokens;

	ignore = 0;
	data = init_data(env);
	if (argc != 1)
	{
		line = argv[1];
		if (!line || ft_strcmp(line, "exit") == 0)
			exit(EXIT_FAILURE);
		tokens = parse_command(data, line);
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		line = readline("minishell 👅👀>  ");
		if (!line || ft_strcmp(line, "exit") == 0)
			break ;
		add_history(line);
		tokens = parse_command(data, line);
	}
	free(line);
	exit(EXIT_FAILURE);
}
