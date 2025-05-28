/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:18:52 by wailas            #+#    #+#             */
/*   Updated: 2025/05/27 13:31:45 by wailas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	check_append(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == APPEND)
		{
			if (tmp->next == NULL)
			{
				ft_printf("Missing file after append operator\n");
				return (false);
			}
			if (tmp->next->type != ARG)
			{
				ft_printf("Expected filename after append\n");
				return (false);
			}
			tmp = tmp->next;
			tmp->type = APPEND_FILE;
		}
		tmp = tmp->next;
	}
	return (true);
}

bool	check_infile(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->type == REDIR_IN)
		{
			if (tmp->next == NULL)
			{
				ft_printf("Missing file or delimiter after input redirection\n");
				return (false);
			}
			if (tmp->next->type != ARG)
			{
				ft_printf("Expected filename or delimiter\n");
				return (false);
			}
			tmp = tmp->next;
			tmp->type = INFILE;
		}
		tmp = tmp->next;
	}
	return (true);
}

bool	check_delimiter(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->type == DELIMITEUR)
		{
			if (tmp->next == NULL)
			{
				ft_printf("Missing delimiter after here-doc\n");
				return (false);
			}
			if (tmp->next->type != ARG)
			{
				ft_printf("Expected delimiter after here-doc\n");
				return (false);
			}
			tmp = tmp->next;
			tmp->type = DELIMITEUR_MOT;
		}
		tmp = tmp->next;
	}
	return (true);
}

bool	check_cmd(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	if (tmp->type == ARG)
		tmp->type = CMD;
	tmp = tmp->next;
	while (tmp)
	{
		if (tmp->type == INFILE && tmp->next != NULL && tmp->next->type == ARG)
			tmp->next->type = CMD;
		if (tmp->type == DELIMITEUR_MOT && tmp->next != NULL \
				&& tmp->next->type == ARG)
			tmp->next->type = CMD;
		if (tmp->next != NULL && tmp->type == PIPE)
			tmp->next->type = CMD;
		tmp = tmp->next;
	}
	return (true);
}

void	move_outfiles(t_token	*segment_start)
{
	int		outfile_count;

	outfile_count = count_outfiles(segment_start);
	if (!outfile_count)
		return ;
	while (outfile_count)
	{
		move_outfiles_to_last(segment_start);
		outfile_count--;
	}
}
void	move_outfiles_to_last(t_token *segment_start)
{
	t_token	*cur_type;
	t_token	*to_move_type;
	t_token	*to_move_file;
	t_token	*tmp;

	cur_type = segment_start;
	to_move_type = NULL;
	while (cur_type && cur_type != PIPE)
	{
		if (cur_type->type == REDIR_OUT || cur_type->type == APPEND)
			to_move_type = cur_type;
			to_move_file = cur_type->next;
			break ;
		cur_type = cur_type->next;
	}
	if (!to_move_type || !to_move_file)
		return ;
	

}

void	token_swap(t_token *first, t_token *second)
{
	t_token	*tmp;

	tmp = create_token(first->type, first->value);
	if (!tmp)
		return ;
	first->type = second->type;
	first->value = second->value;
	second->type = tmp->type;
	second->value = tmp->value;
	free(tmp);
}

int		count_outfiles(t_token *segment_start)
{
	t_token	*cur;
	int		count;

	cur = segment_start;
	count = 0;
	while (cur && cur->type != PIPE)
	{
		if (cur->type == REDIR_OUT || cur->type == APPEND)
			count++;
		cur = cur->next;
	}
	return (count);
}