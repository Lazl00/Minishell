/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phoenix_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcournoy <lcournoy@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-28 17:17:49 by lcournoy          #+#    #+#             */
/*   Updated: 2025-05-28 17:17:49 by lcournoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	new_token(t_token **head, t_token *new_token)
{
	t_token *cur;

	if (!new_token)
		return (false);
	new_token->next = NULL;
	if (!*head)
	{
		*head = new_token;
		return (true);
	}
	cur = *head;
	while (cur->next)
		cur = cur->next;
	cur->next = new_token;
	return (true);
}
