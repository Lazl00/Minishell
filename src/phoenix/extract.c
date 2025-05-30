/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 18:06:32 by wailas            #+#    #+#             */
/*   Updated: 2025/05/30 18:08:06 by wailas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	extract_redir_out_pairs(t_token **phoenix, t_token **deprecated)
{
	t_token	*cur = *deprecated;
	t_token	*prev = NULL;

	while (cur && cur->next)
	{
		if (cur->type == REDIR_OUT && cur->next->type == OUTFILE)
		{
			t_token *redir = cur;
			t_token *file = cur->next;

			if (prev)
				prev->next = file->next;
			else
				*deprecated = file->next;

			cur = file->next;

			redir->next = NULL;
			file->next = NULL;

			append_token(phoenix, redir);
			append_token(phoenix, file);
		}
		else
		{
			prev = cur;
			cur = cur->next;
		}
	}
}

void	extract_redir_in_pairs(t_token **phoenix, t_token **deprecated)
{
	t_token *cur = *deprecated;
	t_token *prev = NULL;

	while (cur && cur->next)
	{
		if (cur->type == REDIR_IN && cur->next->type == INFILE)
		{
			t_token *redir = cur;
			t_token *file = cur->next;

			if (prev)
				prev->next = file->next;
			else
				*deprecated = file->next;

			cur = file->next;

			redir->next = NULL;
			file->next = NULL;

			append_token(phoenix, redir);
			append_token(phoenix, file);
		}
		else
		{
			prev = cur;
			cur = cur->next;
		}
	}
}

void	extract_heredoc_pairs(t_token **phoenix, t_token **deprecated)
{
	t_token *cur = *deprecated;
	t_token *prev = NULL;

	while (cur && cur->next)
	{
		if (cur->type == DELIMITEUR && cur->next->type == DELIMITEUR_MOT)
		{
			t_token *redir = cur;
			t_token *word = cur->next;
			if (prev)
				prev->next = word->next;
			else
				*deprecated = word->next;

			cur = word->next;

			redir->next = NULL;
			word->next = NULL;

			append_token(phoenix, redir);
			append_token(phoenix, word);
		}
		else
		{
			prev = cur;
			cur = cur->next;
		}
	}
}

void	extract_args_after_cmd(t_token **phoenix, t_token **deprecated)
{
	t_token	*cur = *deprecated;
	t_token	*prev = NULL;

	while (cur)
	{
		if (cur->type == ARG)
		{
			if (prev)
				prev->next = cur->next;
			else
				*deprecated = cur->next;

			t_token *next = cur->next;
			cur->next = NULL;
			append_token(phoenix, cur);
			cur = next;
		}
		else if (cur->type == PIPE || cur->type == CMD || cur->type == CMD_BUILTIN)
			break;
		else
		{
			prev = cur;
			cur = cur->next;
		}
	}
}
