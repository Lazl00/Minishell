/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   accesses.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:36:38 by wailas            #+#    #+#             */
/*   Updated: 2025/06/17 11:52:31 by wailas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	check_open(t_token *tokens)
{
	t_token	*tmp;
	int		fd;

	if (has_pipe(tokens))
		return (true);
	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == INFILE)
		{
			fd = open(tmp->value, O_RDONLY);
			if (fd < 0)
				return (false);
			close(fd);
		}
		else if (tmp->type == OUTFILE || tmp->type == APPEND_FILE)
		{
			if (!check_file(tmp, &fd))
				return (true);
			close(fd);
		}
		tmp = tmp->next;
	}
	return (true);
}

bool	check_file(t_token *token, int *fd)
{
	if (token->type == OUTFILE)
		*fd = open(token->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (token->type == APPEND_FILE)
		*fd = open(token->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		return (false);
	if (*fd < 0)
	{
		perror(token->value);
		return (false);
	}
	return (true);
}

bool	check_access(t_data *data)
{
	t_token	*tmp;
	char	*temp;

	tmp = data->tokens;
	while (tmp)
	{
		if (tmp->type == CMD)
		{
			if (is_builtin(tmp) == false)
			{
				temp = tmp->value;
				tmp->value = check_exec(data, tmp, data->env);
				free(temp);
				if (tmp->value == NULL)
					return (false);
			}
			else if (is_builtin(tmp) == true)
				tmp->type = CMD_BUILTIN;
		}
		tmp = tmp->next;
	}
	return (true);
}

bool	has_pipe(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == PIPE)
			return (true);
		tokens = tokens->next;
	}
	return (false);
}
