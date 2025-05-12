/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:25:00 by wailas            #+#    #+#             */
/*   Updated: 2025/05/07 14:28:18 by wailas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	lexing(t_data *data)
{
	check_pipe((*data).tokens);
	check_outfile((*data).tokens);
	//check_infile((*data).tokens);
	print_token_list((*data).tokens);
}

void	check_pipe(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->type == PIPE && tmp->next == NULL)
			printf("Don't finish a line with a Pipe\n");
		tmp = tmp->next;
	}
}

void	check_outfile(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if ((tmp->type == REDIR_OUT || tmp->type == APPEND)
			&& tmp->next != NULL)
		{
			tmp = tmp->next;
			tmp->type = OUTFILE;
		}
		tmp = tmp->next;
	}
}

void	check_infile(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if ((tmp->next->type == REDIR_IN || tmp->next->type == DELIMITEUR)
			&& tmp->next != NULL)
		{
			tmp->type = INFILE;
		}
		tmp = tmp->next;
	}
}
