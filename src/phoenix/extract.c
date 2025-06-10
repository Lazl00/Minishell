/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 18:06:32 by wailas            #+#    #+#             */
/*   Updated: 2025/06/02 18:04:52 by wailas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	extract_redir_out_pairs(t_token **phoenix, t_token **deprecated)
{
	t_token	*cur;
	t_token	*prev;

	cur = *deprecated;
	prev = NULL;
	while (cur && cur->next)
	{
		if (cur->type == REDIR_OUT && cur->next->type == OUTFILE)
			move_token_pair(phoenix, deprecated, &cur, &prev);
		else
		{
			prev = cur;
			cur = cur->next;
		}
	}
}

void	extract_redir_in_pairs(t_token **phoenix, t_token **deprecated)
{
	t_token	*cur;
	t_token	*prev;

	cur = *deprecated;
	prev = NULL;
	while (cur && cur->next)
	{
		if ((cur->type == REDIR_IN && cur->next->type == INFILE)
			|| (cur->type == APPEND && cur->next->type == APPEND_FILE))
			move_token_pair(phoenix, deprecated, &cur, &prev);
		else
		{
			prev = cur;
			cur = cur->next;
		}
	}
}

void	extract_heredoc_pairs(t_token **phoenix, t_token **deprecated)
{
	t_token	*cur;
	t_token	*prev;

	cur = *deprecated;
	prev = NULL;
	while (cur && cur->next)
	{
		if (cur->type == DELIMITEUR && cur->next->type == DELIMITEUR_MOT)
			move_token_pair(phoenix, deprecated, &cur, &prev);
		else
		{
			prev = cur;
			cur = cur->next;
		}
	}
}

bool	move_token_pair(
	t_token **phoenix,
	t_token **deprecated,
	t_token **cur,
	t_token **prev
)
{
	t_token	*first;
	t_token	*second;

	first = *cur;
	second = first->next;
	if (!second)
		return (false);
	if (*prev)
		(*prev)->next = second->next;
	else
		*deprecated = second->next;
	*cur = second->next;
	first->next = NULL;
	second->next = NULL;
	append_token(phoenix, first);
	append_token(phoenix, second);
	return (true);
}
