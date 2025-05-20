/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:34:00 by wailas            #+#    #+#             */
/*   Updated: 2025/05/19 17:49:33 by wailas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int has_output_redirection(t_token *cmd)
{
    while (cmd && cmd->type != PIPE)
    {
        if (cmd->type == REDIR_OUT || cmd->type == APPEND)
            return 1;
        cmd = cmd->next;
    }
    return 0;
}

t_token *get_segment_end(t_token *start)
{
    while (start && start->type != PIPE)
        start = start->next;
    return (start);
}

void init_pipes(int *pipe_fd, int *has_pipe, t_token *segment_end)
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

void child_process(t_token *segment, int *prev_pipe, int *pipe_fd, t_data *data)
{
	char **argv;

	if (prev_pipe[0] != -1)
	{
		dup2(prev_pipe[0], STDIN_FILENO);
		close(prev_pipe[0]);
		close(prev_pipe[1]);
	}
	handle_redirections(segment);
	if (pipe_fd[1] != -1 && !has_output_redirection(segment))
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
	if (pipe_fd[0] != -1)
		close(pipe_fd[0]);

	argv = build_argv(segment);
	execve(argv[0], argv, data->env);
	perror("execve");
	exit(1);
}
