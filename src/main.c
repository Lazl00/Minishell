/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:37:50 by wailas            #+#    #+#             */
/*   Updated: 2025/06/17 16:37:59 by wailas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

pid_t	g_signal_pid;

void	norme_main(t_data *data)
{
	if (lexing(data) == false)
	{
		if (data->exit_status != 127 && data->exit_status != 2) //chelou
			data->exit_status = 1;
		free_tokens(data->tokens);
		data->tokens = NULL;
		return ;
	}
	ft_exec(data);
	close_all_heredocs(data->tokens);
	free_tokens(data->tokens);
}

void	norm_signal(t_data *data)
{
	if (g_signal_pid == 130)
	{
		data->exit_status = 130;
		g_signal_pid = 0;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_data	*data;
	int		exit_code;

	exit_code = 0;
	rl_outstream = stderr;
	signal(SIGPIPE, SIG_IGN);
	data = malloc(sizeof(t_data));
	init_data(data, env);
	(void)argv;
	(void)argc;
	rl_catch_signals = 0;
	configure_signals(PARENT);
	minishell_loop(data);
	exit_code = data->exit_status;
	free_data_main(data);
	rl_clear_history();
	exit(exit_code);
}

void	minishell_loop(t_data *data)
{
	char	*line;

	while (1)
	{
		line = readline("Mishell >  ");
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		if (*line == '\0')
		{
			free(line);
			continue ;
		}
		norm_signal(data);
		add_history(line);
		if (!parse_command(data, line))
			continue ;
		norme_main(data);
	}
}
