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

void	exit_execve_errno(void)
{
	if (errno == EACCES)
		exit(126);
	else if (errno == ENOEXEC)
		exit(126);
	else if (errno == ENOENT)
		exit(127);
	else
		exit(1);
}
