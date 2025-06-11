/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:08:37 by lcournoy          #+#    #+#             */
/*   Updated: 2025/05/30 15:03:45 by wailas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_redir_in(t_data *data, t_token *cmd)
{
	int	fd;

	fd = open(cmd->next->value, O_RDONLY);
	if (fd < 0)
	{
		perror("infile");
		close_all_heredocs(data->tokens);
		free_data(data);
		exit(1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	handle_redir_out(t_token *cmd)
{
	int	fd;

	fd = open(cmd->next->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("outfile");
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	handle_append(t_token *cmd)
{
	int	fd;

	fd = open(cmd->next->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror("append");
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	handle_heredoc(t_token *cmd)
{
	dup2(cmd->heredoc_fd, STDIN_FILENO);
	close(cmd->heredoc_fd);
}

void	handle_redirections(t_data *data, t_token *cmd)
{
	t_token	*last_heredoc;

	last_heredoc = find_last_heredoc(cmd);
	while (cmd && cmd->type != PIPE)
	{
		if (cmd->type == REDIR_IN && cmd->next)
			handle_redir_in(data, cmd);
		else if (cmd->type == REDIR_OUT && cmd->next)
			handle_redir_out(cmd);
		else if (cmd->type == APPEND && cmd->next)
			handle_append(cmd);
		else if (cmd->type == DELIMITEUR && cmd == last_heredoc)
			handle_heredoc(cmd);
		cmd = cmd->next;
	}
}
