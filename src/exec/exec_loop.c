/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcournoy <lcournoy@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-27 14:01:58 by lcournoy          #+#    #+#             */
/*   Updated: 2025/05/27 17:15:37 by lcournoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_loop(t_data *data)
{
	t_token	*cmd;
	t_token	*segment_start;
	t_token	*segment_end;
	int		prev_pipe[2];
	int		pipe_fd[2];

	cmd = data->tokens;
	prev_pipe[0] = -1;
	prev_pipe[1] = -1;
	while (cmd)
	{
		segment_start = cmd;
		segment_end = get_segment_end(segment_start);
		process_segment(data, segment_start, prev_pipe, pipe_fd);
		update_prev_pipe(prev_pipe, pipe_fd);
		if (segment_end)
			cmd = segment_end->next;
		else
			cmd = NULL;
	}
}

void	process_segment(t_data *data, t_token *start, int prev[2], int pipe[2])
{
	int		has_pipe;
	pid_t	pid;
	t_token	*end;

	end = get_segment_end(start);
	has_pipe = 0;
	if (end && end->next && end->next->type == PIPE)
		has_pipe = 1;
	init_pipes(pipe, &has_pipe, end);
	if (is_builtin(start) && has_pipe == 0 && prev[0] == -1)
		data->exit_status = do_builtin(data, start);
	else
	{
		pid = fork();
		if (pid == 0)
			exec_child(data, start, prev, pipe);
		else if (pid < 0)
		{
			perror("fork");
			exit(1);
		}
	}
}

void	exec_child(t_data *data, t_token *start,
					int prev_pipe[2], int pipe_fd[2])
{
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
	handle_redirections(start);
	exec_dispatch(data, start);
}

void	exec_external(t_data *data, t_token *start)
{
	char	**argv;

	if (!start || !start->value)
	{
		free_data(data);
		exit(127);
	}
	argv = build_argv(start);
	if (!argv)
	{
		free_data(data);
		exit(1);
	}
	execve(start->value, argv, data->env);
	perror("execve");
	free(argv);
	free_data(data);
	exit_execve_errno();
}
