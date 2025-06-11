/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:54:50 by lcournoy          #+#    #+#             */
/*   Updated: 2025/06/11 18:10:11 by lcournoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	prepare_heredocs(t_data *data, t_token *tokens)
{
	t_token	*tmp;
	int		fd;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == 7 && tmp->next && tmp->next->type == 8)
		{
			fd = do_heredoc(data, tmp->next->value, NULL);
			if (fd < 0)
			{
				perror("heredoc");
				exit(1);
			}
			tmp->heredoc_fd = fd;
		}
		tmp = tmp->next;
	}
}

int	do_heredoc(t_data *data, char *delimiter, char *line)
{
	int		pipe_fd[2];
	char	*expanded;

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		expanded = expend_vars(*data, line, 0, 0);
		if (strcmp(expanded, delimiter) == 0)
		{
			free(expanded);
			break ;
		}
		write(pipe_fd[1], expanded, strlen(expanded));
		write(pipe_fd[1], "\n", 1);
		free(expanded);
	}
	close(pipe_fd[1]);
	return (pipe_fd[0]);
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
	while (tokens)
	{
		if (tokens->heredoc_fd != -1)
		{
			close(tokens->heredoc_fd);
			tokens->heredoc_fd = -1;
		}
		tokens = tokens->next;
	}
}
