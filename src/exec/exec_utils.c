/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:34:00 by wailas            #+#    #+#             */
/*   Updated: 2025/05/22 14:49:28 by lcournoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	has_output_redirection(t_token *cmd)
{
	while (cmd && cmd->type != PIPE)
	{
		if (cmd->type == REDIR_OUT || cmd->type == APPEND)
			return (1);
		cmd = cmd->next;
	}
	return (0);
}

t_token	*get_segment_end(t_token *start)
{
	while (start && start->type != PIPE)
		start = start->next;
	return (start);
}

void	init_pipes(int *pipe_fd, int *has_pipe, t_token *segment_end)
{
	*has_pipe = 0;
	if (segment_end && segment_end->type == PIPE)
	{
		*has_pipe = 1;
		if (pipe(pipe_fd) < 0)
		{
			perror("pipe");
			exit(1);
		}
	}
	else
	{
		pipe_fd[0] = -1;
		pipe_fd[1] = -1;
	}
}

void	child_process(t_token *cmd, int prev_pipe[2], int pipe_fd[2], t_data *data)
{
	char	**argv;
	t_token	*exec_cmd;

	handle_redirections(cmd);
	if (prev_pipe[0] != -1)
	{
		dup2(prev_pipe[0], STDIN_FILENO);
		close(prev_pipe[0]);
		close(prev_pipe[1]);
	}
	if (pipe_fd[1] != -1)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
	exec_cmd = cmd;
	while (exec_cmd && exec_cmd->type != CMD)
		exec_cmd = exec_cmd->next;
	argv = build_argv(cmd);
	if (!argv)
		exit(1);
	if (exec_cmd && exec_cmd->type == CMD && exec_cmd->value)
		execve(exec_cmd->value, argv, data->env);
	free_data(data);
	free_tab(argv);
	free_tokens(cmd);
	exit(1);
}