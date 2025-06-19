/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcournoy <lcournoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:54:50 by lcournoy          #+#    #+#             */
/*   Updated: 2025/06/20 01:22:21 by lcournoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void close_all_except(int keep1, int keep2)
{
	for (int fd = 3; fd < 1024; fd++) {
		if (fd != keep1 && fd != keep2)
			close(fd);
	}
}

int	prepare_heredocs(t_data *data, t_token *tokens)
{
	t_token	*tmp;
	int fd;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == 7 && tmp->next && tmp->next->type == 8)
		{
			fd = do_heredoc(data, tmp->next->value, NULL);
			if (fd < 0)
			{
				close_all_heredocs(data->tokens);
				return (-1);
			}
			tmp->heredoc_fd = fd;
		}
		tmp = tmp->next;
	}
	return (1);
}

void	sigint_handler_heredoc(int sig)
{
	(void)sig;
	exit_pipe(-1);
	exit_str(NULL, 0);
	exit_buffer(NULL);
	buf_manager(NULL);
	exit_hdoc(NULL);
	exit(42);
}

t_token	*find_last_heredoc(t_token *cmd)
{
	t_token	*last;

	last = NULL;
	while (cmd && cmd->type != PIPE)
	{
		if (cmd->type == DELIMITEUR && cmd->heredoc_fd != -1)
			last = cmd;
		cmd = cmd->next;
	}
	return (last);
}

void	close_all_heredocs(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->heredoc_fd != -1)
		{
			close(tmp->heredoc_fd);
			tmp->heredoc_fd = -1;
		}
		tmp = tmp->next;
	}
}
