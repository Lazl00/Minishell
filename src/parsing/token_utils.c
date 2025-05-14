/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:17:06 by wailas            #+#    #+#             */
/*   Updated: 2025/05/14 15:28:05 by wailas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

const char* nom_tokens[] = {
	"CMD",
	"REDIR_IN",
	"REDIR_OUT",
	"PIPE",
	"OUTFILE",
	"INFILE",
	"DELIMITEUR",
	"DELIMITEUR_MOT",
	"APPEND",
	"APPEND_FILE",
	"ARG"
};

void	token_remove_quote(t_token *list)
{
	t_token	*tmp;
	char	*new_line;

	tmp = list;
	while (tmp != NULL)
	{
		if (tmp->type == ARG)
		{
			new_line = quotes_remover(tmp->value);
			free(tmp->value);
			tmp->value = new_line;
		}
		tmp = tmp->next;
	}
}

void	access_token_cmd(t_token *list)
{
	t_token	*tmp;

	tmp = list;
	while (tmp != NULL)
	{
		if (tmp->type == ARG)
		{
			if (access(tmp->value, X_OK) == 0)
				tmp->type = CMD;
		}
		tmp = tmp->next;
	}
}

bool	add_token_to_list(t_token **h, t_token **l, t_token *t)
{
	if (!t)
		return (false);
	t->next = NULL;
	if (!*h)
		*h = t;
	else
		(*l)->next = t;
	*l = t;
	return (true);
}

void	print_token_list(t_token *head)
{
	t_token	*tmp;

	tmp = head;
	while (tmp)
	{
		ft_printf("Token : %s\t\tType : %d (%s)\n", \
			tmp->value, tmp->type, nom_tokens[tmp->type]);
		tmp = tmp->next;
	}
}

bool	is_quoted(char *str)
{
	while (*str)
	{
		if (*str == '\'' || *str == '"')
			return (true);
		str++;
	}
	return (false);
}
