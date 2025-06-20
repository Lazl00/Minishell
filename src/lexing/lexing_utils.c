/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:18:52 by wailas            #+#    #+#             */
/*   Updated: 2025/06/02 16:16:23 by wailas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	check_append(t_data *data)
{
	t_token	*tmp;

	tmp = data->tokens;
	while (tmp)
	{
		if (tmp->type == APPEND)
		{
			if (tmp->next == NULL)
			{
				write(2, "Missing file after append operator\n", 36);
				data->exit_status = 2;
				return (false);
			}
			if (tmp->next->type != ARG)
			{
				write(2, "Expected filename after append\n", 32);
				data->exit_status = 2;
				return (false);
			}
			tmp = tmp->next;
			tmp->type = APPEND_FILE;
		}
		tmp = tmp->next;
	}
	return (true);
}

bool	check_infile(t_data *data)
{
	t_token	*tmp;

	tmp = data->tokens;
	while (tmp)
	{
		if (tmp->type == REDIR_IN)
		{
			if (tmp->next == NULL)
			{
				write(2, "Missing file or delimiter after input redirection\n", 21);
				data->exit_status = 2;
				return (false);
			}
			if (tmp->next->type != ARG)
			{
				write(2, "Expected filename or delimiter\n", 32);
				data->exit_status = 2;
				return (false);
			}
			tmp = tmp->next;
			tmp->type = INFILE;
		}
		tmp = tmp->next;
	}
	return (true);
}

bool	check_delimiter(t_data *data)
{
	t_token	*tmp;

	tmp = data->tokens;
	while (tmp)
	{
		if (tmp->type == DELIMITEUR)
		{
			if (tmp->next == NULL)
			{
				write(2, "Missing delimiter after here-doc\n", 34);
				data->exit_status = 2;
				return (false);
			}
			if (tmp->next->type != ARG)
			{
				write(2, "Expected delimiter after here-doc\n", 35);
				data->exit_status = 2;
				return (false);
			}
			tmp = tmp->next;
			tmp->type = DELIMITEUR_MOT;
		}
		tmp = tmp->next;
	}
	return (true);
}

bool	check_cmd(t_token *token)
{
	t_token	*tmp;
	bool	must_be_cmd;

	must_be_cmd = true;
	tmp = token;
	while (tmp)
	{
		if (tmp->type == ARG && must_be_cmd == true)
		{
			if (is_builtin(tmp))
				tmp->type = CMD_BUILTIN;
			else
				tmp->type = CMD;
			must_be_cmd = false;
		}
		if (tmp->next != NULL && tmp->type == PIPE)
			must_be_cmd = true;
		tmp = tmp->next;
	}
	return (true);
}
