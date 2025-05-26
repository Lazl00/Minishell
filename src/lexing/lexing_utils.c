/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:18:52 by wailas            #+#    #+#             */
/*   Updated: 2025/05/14 17:54:45 by wailas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	check_append(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == APPEND)
		{
			if (tmp->next == NULL)
			{
				ft_printf("Missing file after append operator\n");
				return (false);
			}
			if (tmp->next->type != ARG)
			{
				ft_printf("Expected filename after append\n");
				return (false);
			}
			tmp = tmp->next;
			tmp->type = APPEND_FILE;
		}
		tmp = tmp->next;
	}
	return (true);
}

bool	check_infile(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->type == REDIR_IN)
		{
			if (tmp->next == NULL)
			{
				ft_printf("Missing file or delimiter after input redirection\n");
				return (false);
			}
			if (tmp->next->type != ARG)
			{
				ft_printf("Expected filename or delimiter\n");
				return (false);
			}
			tmp = tmp->next;
			tmp->type = INFILE;
		}
		tmp = tmp->next;
	}
	return (true);
}

bool	check_delimiter(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->type == DELIMITEUR)
		{
			if (tmp->next == NULL)
			{
				ft_printf("Missing delimiter after here-doc\n");
				return (false);
			}
			if (tmp->next->type != ARG)
			{
				ft_printf("Expected delimiter after here-doc\n");
				return (false);
			}
			tmp = tmp->next;
			tmp->type = DELIMITEUR_MOT;
		}
		tmp = tmp->next;
	}
	return (true);
}

bool    check_cmd(t_token *token)
{
	t_token *tmp;

	tmp = token;
	if (tmp->type == ARG)
		tmp->type = CMD;
	tmp = tmp->next;
	while (tmp)
	{
		if (tmp->type == INFILE && tmp->next != NULL && tmp->next->type == ARG)
			tmp->next->type = CMD;
		if (tmp->next != NULL && tmp->type == PIPE)
			tmp->next->type = CMD;
		tmp = tmp->next;
	}
	return (true);
}

