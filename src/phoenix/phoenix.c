/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phoenix.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:00:57 by lcournoy          #+#    #+#             */
/*   Updated: 2025/05/30 18:18:54 by wailas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	append_token(t_token **head, t_token *to_add)
{
	if (!to_add)
		return ;
	to_add->next = NULL;
	if (!*head)
	{
		*head = to_add;
		return ;
	}
	t_token *cur = *head;
	while (cur->next)
		cur = cur->next;
	cur->next = to_add;
}

void	add_all_matching_tokens(t_token **phoenix, t_token **deprecated, t_token *(*finder)(t_token **))
{
	t_token	*to_add;
	while ((to_add = finder(deprecated)))
		append_token(phoenix, to_add);
}

t_token	*find_next_token_of_type(t_token **deprecated, t_enum_token type)
{
	t_token	*cur = *deprecated;
	t_token	*prev = NULL;

	while (cur)
	{
		if (cur->type == type)
		{
			if (prev)
				prev->next = cur->next;
			else
				*deprecated = cur->next;
			cur->next = NULL;
			return cur;
		}
		prev = cur;
		cur = cur->next;
	}
	return (NULL);
}

t_token	*find_cmd_phoenix(t_token **deprecated)
{
	t_token	*cur = *deprecated;
	t_token	*prev = NULL;

	while (cur)
	{
		if (cur->type == CMD || cur->type == CMD_BUILTIN)
		{
			if (prev)
				prev->next = cur->next;
			else
				*deprecated = cur->next;
			cur->next = NULL;
			return (cur);
		}
		prev = cur;
		cur = cur->next;
	}
	return (NULL);
}
