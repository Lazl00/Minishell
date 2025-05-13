/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:25:00 by wailas            #+#    #+#             */
/*   Updated: 2025/05/13 17:48:36 by wailas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	lexing(t_data *data)
{
	if (!check_pipe((*data).tokens))
	check_outfile((*data).tokens);
	check_infile((*data).tokens);
	check((*data).tokens);
	here_doc(data, "salut");
	print_token_list((*data).tokens);
}

bool check_pipe(t_token *tokens)
{
    t_token *tmp;

    tmp = tokens;
    while (tmp)
    {
        if (tmp->type == PIPE && tmp == tokens)
            return (print_error("Pipe at the beginning of the line\n"));
        if (tmp->type == PIPE && tmp->next == NULL)
			return (print_error("Pipe at the end of the line\n"));
        if (tmp->type == PIPE && tmp->next != NULL && tmp->next->type == PIPE)
			return (print_error("Two pipes in a row\n"));
        if (tmp->type == PIPE && (tmp->next == NULL || tmp->next->type != ARG))
			return (print_error("Pipe not followed by a command\n"));
        tmp = tmp->next;
    }
    return (true);
}

void	check_outfile(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == REDIR_OUT || tmp->type == APPEND)
		{
			if (tmp->next == NULL)
			{
				ft_printf("Missing argument after an operator");
				return ;
			}
			if (tmp->next->type != ARG)
			{
				ft_printf("The next value must be an argument");
				return ;
			}
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
		if (tmp->next != NULL && (tmp->next->type == REDIR_IN
				|| tmp->next->type == DELIMITEUR))
		{
			tmp->type = INFILE;
		}
		tmp = tmp->next;
	}
}

void	check(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if ((tmp->type == DELIMITEUR || tmp->type == APPEND
				|| tmp->type == REDIR_IN || tmp->type == REDIR_OUT)
			&& tmp->next == NULL)
			printf("Dont Finish a line with redirection empty\n");
		tmp = tmp->next;
	}
}
