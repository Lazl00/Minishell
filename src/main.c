/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 16:48:31 by lcournoy          #+#    #+#             */
/*   Updated: 2025/05/14 18:19:14 by wailas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
	char			*line;
	t_data			*data;

	data = malloc(sizeof(t_data));
	init_data(data, env);
	if (argc != 1)
	{
		line = argv[1];
		if (!line || ft_strcmp(line, "exit") == 0)
			exit(EXIT_FAILURE);
		parse_command(data, line);
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		print_str_array(data->env);
		line = readline("minishell 👅👀>  ");
		if (!line || ft_strcmp(line, "exit") == 0)
			break ;
		add_history(line);
		parse_command(data, line);
		lexing(data);
		check_access(data);
		free_tokens(data->tokens);
	}
	free_data(data);
	exit(EXIT_FAILURE);
}
