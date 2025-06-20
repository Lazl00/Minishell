/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:25:16 by wailas            #+#    #+#             */
/*   Updated: 2025/06/17 15:08:23 by wailas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**build_argv(t_token *cmd)
{
	t_token	*tmp;
	int		i;
	char	**argv;

	i = 0;
	tmp = cmd;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == CMD || tmp->type == ARG)
			i++;
		tmp = tmp->next;
	}
	argv = malloc(sizeof(char *) * (i + 1));
	if (!argv)
		return (NULL);
	tmp = cmd;
	i = 0;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == CMD || tmp->type == ARG)
			argv[i++] = tmp->value;
		tmp = tmp->next;
	}
	argv[i] = NULL;
	return (argv);
}

t_token	*find_first_cmd(t_token *segment_start)
{
	t_token	*cur;

	cur = segment_start;
	while (cur && cur->type != PIPE)
	{
		if (cur->type == CMD || cur->type == CMD_BUILTIN || cur->type == ARG)
			return (cur);
		cur = cur->next;
	}
	return (NULL);
}

void	ft_exec(t_data *data)
{
	int		status;
	pid_t	pid;

	signal(SIGINT, SIG_IGN);
	prepare_heredocs(data, data->tokens);
	if (g_signal_pid == 42)
	{
		data->exit_status = 130;
		g_signal_pid = 0;
		close_all_heredocs(data->tokens);
		return ;
	}
	exec_loop(data);
	pid = wait(&status);
	while (pid > 0)
	{
		if (pid == g_signal_pid)
			data->exit_status = interpret_status(status);
		pid = wait(&status);
	}
	close_all_heredocs(data->tokens);
	signal(SIGINT, sigint_handler);
}

int	interpret_status(int status)
{
	int	sig;

	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
		{
			write(2, "\n", 1);
			return (130);
		}
		else if (sig == SIGQUIT)
		{
			write(2, "Quit (core dumped)\n", 20);
			return (131);
		}
		return (128 + sig);
	}
	return (1);
}
