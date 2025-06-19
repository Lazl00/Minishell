/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcournoy <lcournoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:01:58 by lcournoy          #+#    #+#             */
/*   Updated: 2025/06/19 21:32:41 by lcournoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_heredocs(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		printf("%s\t%d\n", tmp->value, tmp->heredoc_fd);
		tmp = tmp->next;
	}
}
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

void	exec_in_child(t_data *data, t_token *start, int prev[2], int pipe[2])
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	exec_child(data, start, prev, pipe);
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
		data->exit_status = do_builtin(data, start);
		return (-1);
	}
	write(2, "fork exec\n", 11);
	pid = fork();
	if (pid == 0)
		exec_in_child(data, start, prev, pipe);
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
	handle_redirections(data, start);
	exec_dispatch(data, start);
}

void	exec_external(t_data *data, t_token *start)
{
	char	**argv;

	if (!start || !start->value)
	{
		close_all_heredocs(data->tokens);
		free_data(data);
		exit(127);
	}
	argv = build_argv(start);
	if (!argv)
	{
		close_all_heredocs(data->tokens);
		free_data(data);
		exit(1);
	}
	close_all_heredocs(data->tokens);
	execve(start->value, argv, data->env);
	free(argv);
	free_data(data);
	exit_execve_errno();
}
//cat << s | cat << d | cat << f | cat << g