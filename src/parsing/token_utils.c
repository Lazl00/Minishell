/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcournoy <lcournoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:17:06 by wailas            #+#    #+#             */
/*   Updated: 2025/04/30 14:15:30 by lcournoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	token_remove_quote(t_token_node *list)
{
	t_token_node	*tmp;
	char			*new_line;

	tmp = list;
	while (tmp != NULL)
	{
		if (tmp->token->type == token_arg)
		{
			new_line = quotes_remover(tmp->token->value);
			free(tmp->token->value);
			tmp->token->value = new_line;
		}
		tmp = tmp->next;
	}
}

void	access_token_cmd(t_token_node *list)
{
	t_token_node	*tmp;

	tmp = list;
	while (tmp != NULL)
	{
		if (tmp->token->type == token_arg)
		{
			printf("ta valeur tiens : %s\n", tmp->token->value);
			if (access(tmp->token->value, X_OK) == 0)
			{
				tmp->token->type = token_cmd;
				printf("ta les droits chef\n");
			}
		}
		tmp = tmp->next;
	}
}
