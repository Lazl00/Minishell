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
		close_all_heredocs(data->tokens);
		free_data(data);
		exit(exit_code);
	}
	else
	{
		exec_external(data, start);
	}
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
