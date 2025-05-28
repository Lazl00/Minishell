/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:25:16 by wailas            #+#    #+#             */
/*   Updated: 2025/05/28 14:53:22 by lcournoy         ###   ########.fr       */
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

void	update_pipe_and_cmd(int p[2], t_token *s, t_token **cmd, int pipe_fd[2])
{
	if (p[0] != -1)
	{
		close(p[0]);
		close(p[1]);
	}
	p[0] = pipe_fd[0];
	p[1] = pipe_fd[1];
	if (s)
		*cmd = s->next;
	else
		*cmd = NULL;
}

void ft_exec(t_data *data)
{
	int status;
	pid_t pid;

	prepare_heredocs(data->tokens);
	exec_loop(data);
	pid = wait(&status);
	while (pid > 0)
	{
		if (pid == g_signal_pid) 
		{
			if (WIFEXITED(status))
				data->exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				int sig = WTERMSIG(status);
				if (sig == SIGINT)
					data->exit_status = 130;
				else
					data->exit_status = 128 + sig;
			}
		}
		pid = wait(&status);
	}
}
