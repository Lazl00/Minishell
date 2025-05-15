/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:00:58 by wailas            #+#    #+#             */
/*   Updated: 2025/05/15 14:20:23 by wailas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	build_cmd_list(t_token *tokens, t_cmd **cmd_list)
{
	t_token	*tmp;
	t_cmd	*curr_cmd = NULL;

    tmp = tokens;
	while (tmp)
	{
		if (tmp->type == CMD)
		{
			curr_cmd = init_cmd(tmp->value);
			tmp = fill_cmd_fields(curr_cmd, tmp->next);
			if (tmp && tmp->type == PIPE)
			{
				curr_cmd->pipe_out = true;
				pipe(curr_cmd->pipe_fd);
			}
			ft_lstadd_back_cmd(cmd_list, curr_cmd);
		}
		else
			tmp = tmp->next;
	}
	return (true);
}

t_cmd	*init_cmd(char *cmd_name)
{
	t_cmd *cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->infile = STDIN_FILENO;
	cmd->outfile = STDOUT_FILENO;
	cmd->append_out = false;
	cmd->pipe_out = false;
	cmd->skip_cmd = false;
	cmd->heredoc = false;
	add_param(&cmd->cmd_param, cmd_name);
	return (cmd);
}

t_token	*fill_cmd_fields(t_cmd *cmd, t_token *tmp)
{
	while (tmp && tmp->type != CMD && tmp->type != PIPE)
	{
		if (tmp->type == ARG)
			add_param(&cmd->cmd_param, tmp->value);
		else if (tmp->type == REDIR_IN && tmp->next)
			handle_redir_in(cmd, tmp->next->value);
		else if (tmp->type == REDIR_OUT && tmp->next)
			handle_redir_out(cmd, tmp->next->value);
		else if (tmp->type == APPEND && tmp->next)
			handle_append(cmd, tmp->next->value);
		else if (tmp->type == DELIMITEUR && tmp->next)
			handle_heredoc_token(cmd, tmp->next->value);
		tmp = tmp->next;
	}
	return (tmp);
}

