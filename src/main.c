/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:37:50 by wailas            #+#    #+#             */
/*   Updated: 2025/05/27 14:37:54 by wailas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

pid_t	g_signal_pid;

int	main(int argc, char **argv, char **env)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	init_data(data, env);
	(void)argv;
	(void)argc;
	rl_catch_signals = 0;
	configure_signals(PARENT);
	minishell_loop(data);
	free_data_main(data);
	exit(EXIT_FAILURE);
}

void	minishell_loop(t_data *data)
{
	char	*line;

	while (1)
	{
		line = readline("minishell 👅👀>  ");
		if (!line)
			break ;
		if (*line == '\0')
		{
			free(line);
			continue ;
		}
		add_history(line);
		if (!parse_command(data, line))
		{
			free(line);
			continue ;
		}
		lexing(data);
		ft_exec(data);
		free_tokens(data->tokens);
	}
}
