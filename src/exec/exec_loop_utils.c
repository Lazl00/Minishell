/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_loop_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcournoy <lcournoy@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-27 15:21:27 by lcournoy          #+#    #+#             */
/*   Updated: 2025-05-27 15:21:27 by lcournoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_dispatch(t_data *data, t_token *start)
{
	int	exit_code;

	if (is_builtin(start))
	{
		exit_code = do_builtin(data, start);
		free_data(data);
		exit(exit_code);
	}
	else
		exec_external(data, start);
}

void	update_prev_pipe(int prev_pipe[2], int pipe_fd[2])
{
	if (prev_pipe[0] != -1)
	{
		close(prev_pipe[0]);
		close(prev_pipe[1]);
	}
	prev_pipe[0] = pipe_fd[0];
	prev_pipe[1] = pipe_fd[1];
}

void	setup_pipes_and_redirects(t_token *cmd, int prev[2], int fds[2])
{
	handle_redirections(cmd);
	if (prev[0] != -1)
	{
		dup2(prev[0], STDIN_FILENO);
		close(prev[0]);
		close(prev[1]);
	}
	if (fds[1] != -1)
	{
		dup2(fds[1], STDOUT_FILENO);
		close(fds[0]);
		close(fds[1]);
	}
}
