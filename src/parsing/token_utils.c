/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:17:06 by wailas            #+#    #+#             */
/*   Updated: 2025/06/04 13:58:49 by wailas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

const char	*g_nom_tokens[] = {
	"CMD",
	"CMD_BUILTIN",
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

bool	add_token_to_list(t_token **head, t_token **last, t_token *nw_tok)
{
	if (!nw_tok)
		return (false);
	nw_tok->next = NULL;
	if (!*head)
		*head = nw_tok;
	else
		(*last)->next = nw_tok;
	*last = nw_tok;
	return (true);
}

const char	*get_token_type_name(t_enum_token type)
{
	if (type == CMD)
		return ("CMD");
	if (type == CMD_BUILTIN)
		return ("CMD_BUILTIN");
	if (type == REDIR_IN)
		return ("REDIR_IN");
	if (type == REDIR_OUT)
		return ("REDIR_OUT");
	if (type == PIPE)
		return ("PIPE");
	if (type == OUTFILE)
		return ("OUTFILE");
	if (type == INFILE)
		return ("INFILE");
	if (type == DELIMITEUR)
		return ("DELIMITEUR");
	if (type == DELIMITEUR_MOT)
		return ("DELIM_MOT");
	if (type == APPEND)
		return ("APPEND");
	if (type == APPEND_FILE)
		return ("APPEND_FILE");
	if (type == ARG)
		return ("ARG");
	return ("UNKNOWN");
}

void	print_token_list(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens)
	{
		printf("[%02d] Token : %-15s | Type : %-12s (%d)\n",
			i, tokens->value, get_token_type_name(tokens->type), tokens->type);
		if (tokens->type == PIPE)
			printf("─────────── 🔁 PIPE ───────────\n");
		tokens = tokens->next;
		i++;
	}
	printf("\n\n");
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
