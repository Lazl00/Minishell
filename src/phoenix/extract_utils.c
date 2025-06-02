/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 18:06:30 by wailas            #+#    #+#             */
/*   Updated: 2025/06/02 18:07:10 by wailas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	move_arg_token(t_token **phoenix, t_token **deprecated,
	t_token **cur, t_token **prev)
{
	t_token	*next;

	if (*prev)
		(*prev)->next = (*cur)->next;
	else
		*deprecated = (*cur)->next;
	next = (*cur)->next;
	(*cur)->next = NULL;
	append_token(phoenix, *cur);
	*cur = next;
}

void	extract_args_after_cmd(t_token **phoenix, t_token **deprecated)
{
	t_token	*cur;
	t_token	*prev;

	cur = *deprecated;
	prev = NULL;
	while (cur)
	{
		if (cur->type == ARG)
			move_arg_token(phoenix, deprecated, &cur, &prev);
		else if (cur->type == PIPE || cur->type == CMD
			|| cur->type == CMD_BUILTIN)
			break ;
		else
		{
			prev = cur;
			cur = cur->next;
		}
	}
}
