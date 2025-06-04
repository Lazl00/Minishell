/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:37:50 by wailas            #+#    #+#             */
/*   Updated: 2025/06/04 14:20:34 by wailas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

pid_t	g_signal_pid;

void	norme_main(t_data *data)
{
	lexing(data);
	ft_exec(data);
	free_tokens(data->tokens);
}

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
		line = readline("Mishell >  ");
		if (!line)
			break ;
		if (*line == '\0')
		{
			free(line);
			continue ;
		}
		if (g_signal_pid == 130)
		{
			data->exit_status = 130;
			g_signal_pid = 0;
		}
		add_history(line);
		if (!parse_command(data, line))
		{
			free(line);
			continue ;
		}
		norme_main(data);
	}
}
