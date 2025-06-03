/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:01:58 by lcournoy          #+#    #+#             */
/*   Updated: 2025/06/03 16:44:29 by wailas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_loop(t_data *data)
{
	t_exec_context	ctx;

	ctx.cmd = data->tokens;
	ctx.prev_pipe[0] = -1;
	ctx.prev_pipe[1] = -1;
	ctx.last_pid = -1;
	while (ctx.cmd)
	{
		ctx.segment_start = ctx.cmd;
		ctx.segment_end = get_segment_end(ctx.segment_start);
		ctx.last_pid = process_segment(data, ctx.segment_start,
				ctx.prev_pipe, ctx.pipe_fd);
		update_prev_pipe(ctx.prev_pipe, ctx.pipe_fd);
		if (ctx.segment_end)
			ctx.cmd = ctx.segment_end->next;
		else
			ctx.cmd = NULL;
	}
	g_signal_pid = ctx.last_pid;
}

pid_t	process_segment(t_data *data, t_token *start, int prev[2], int pipe[2])
{
	t_token	*end;
	int		has_pipe;
	pid_t	pid;

	end = get_segment_end(start);
	has_pipe = 0;
	if (end && end->next && end->next->type == PIPE)
		has_pipe = 1;
	init_pipes(pipe, &has_pipe, end);
	if (is_builtin(start) && has_pipe == 0 && prev[0] == -1)
	{
		g_signal_pid = do_builtin(data, start); // si le do_builtin marche -> renvoie 0, si il echoue, je pense renvoie a tous les coups 127
		return (-1);							// bordel
	}
	pid = fork();
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		exec_child(data, start, prev, pipe);
	}
	else if (pid < 0)
	{
		perror("fork");
		free_data(data);
		exit(1);
	}
	return (pid);
}

void	exec_child(t_data *data, t_token *start, int prev[2], int pipe_fd[2])
{
	if (prev[0] != -1)
	{
		dup2(prev[0], STDIN_FILENO);
		close(prev[0]);
		close(prev[1]);
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
	free(argv);
	free_data(data);
	exit_execve_errno();
}
