/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phoenix.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:00:57 by lcournoy          #+#    #+#             */
/*   Updated: 2025/05/30 16:52:44 by lcournoy         ###   ########.fr       */
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


void	remove_redundant_outfiles(t_token **lst)
{
	t_token *cur = *lst;
	t_token *prev = NULL;
	t_token *last_out_sign = NULL;
	t_token *last_out_file = NULL;

	while (cur)
	{
		if (cur->type == REDIR_OUT)
			last_out_sign = cur;
		else if (cur->type == OUTFILE)
			last_out_file = cur;

		cur = cur->next;
	}
	cur = *lst;
	prev = NULL;
	while (cur)
	{
		int is_old_redir = (cur->type == REDIR_OUT && cur != last_out_sign);
		int is_old_file = (cur->type == OUTFILE && cur != last_out_file);

		if (is_old_redir || is_old_file)
		{
			t_token *to_delete = cur;
			if (prev)
				prev->next = cur->next;
			else
				*lst = cur->next;
			cur = cur->next;
			free(to_delete->value);
			free(to_delete);
		}
		else
		{
			prev = cur;
			cur = cur->next;
		}
	}
}

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


t_token	*phoenix(t_token **deprecated)
{
	t_token *phoenix = NULL;
	t_token *to_add;
	t_token *segment = NULL;
	t_token *after_pipe = NULL;

	while (*deprecated)
	{
		t_token *cur = *deprecated;
		t_token *prev = NULL;
		segment = cur;

		while (cur && cur->type != PIPE)
		{
			prev = cur;
			cur = cur->next;
		}
		if (cur && cur->type == PIPE)
		{
			after_pipe = cur->next;
			cur->next = NULL;
		}
		else
			after_pipe = NULL;
		to_add = find_cmd_phoenix(&segment);
		if (to_add)
			append_token(&phoenix, to_add);
		extract_args_after_cmd(&phoenix, &segment);
		extract_redir_in_pairs(&phoenix, &segment);
		extract_heredoc_pairs(&phoenix, &segment);
		extract_redir_out_pairs(&phoenix, &segment);
		add_all_matching_tokens(&phoenix, &segment, find_append_signe_phoenix);
		add_all_matching_tokens(&phoenix, &segment, find_append_file_phoenix);
		add_all_matching_tokens(&phoenix, &segment, find_delimiteur_phoenix);
		add_all_matching_tokens(&phoenix, &segment, find_delimiteur_mot_phoenix);
		if (cur && cur->type == PIPE)
			append_token(&phoenix, cur);
		*deprecated = after_pipe;
	}

	return phoenix;
}

