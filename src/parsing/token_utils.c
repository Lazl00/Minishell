/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:17:06 by wailas            #+#    #+#             */
/*   Updated: 2025/04/30 16:41:05 by wailas           ###   ########.fr       */
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
		if (tmp->token->type == ARG)
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
		if (tmp->token->type == ARG)
		{
			printf("ta valeur tiens : %s\n", tmp->token->value);
			if (access(tmp->token->value, X_OK) == 0)
			{
				tmp->token->type = CMD;
				printf("ta les droits chef\n");
			}
		}
		tmp = tmp->next;
	}
}

bool	add_token_to_list(t_token_node **h, t_token_node **l, t_token *t)
{
	t_token_node	*new_node;

	new_node = malloc(sizeof(t_token_node));
	if (!new_node)
		return (false);
	new_node->token = t;
	new_node->next = NULL;
	if (!*h)
		*h = new_node;
	else
		(*l)->next = new_node;
	*l = new_node;
	return (true);
}

void	print_token_list(t_token_node *head)
{
	t_token_node	*tmp;

	tmp = head;
	while (tmp)
	{
		ft_printf("Token : %s | Type : %d\n", \
			tmp->token->value, tmp->token->type);
		tmp = tmp->next;
	}
}

bool	token(char *input)
{
	char			*input_copy;
	char			*token_value;
	t_token			*new_token;
	t_token_node	*head;
	t_token_node	*last;

	last = NULL;
	head = NULL;
	input_copy = input_with_space(input);
	if (!input_copy)
		return (false);
	token_value = ft_strtok(input_copy, " \t\n");
	while (token_value)
	{
		new_token = create_token_from_value(token_value);
		if (!add_token_to_list(&head, &last, new_token))
			return (false);
		token_value = ft_strtok(NULL, " \t\n");
	}
	free(input_copy);
	token_remove_quote(head);
	access_token_cmd(head);
	print_token_list(head);
	return (true);
}
