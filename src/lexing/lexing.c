/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:25:00 by wailas            #+#    #+#             */
/*   Updated: 2025/05/30 15:06:29 by wailas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	lexing(t_data *data)
{
	t_token	*clean_tokens;

	if (!check_pipe(data->tokens))
		return (false);
	if (!check_outfile(data->tokens) || !check_append(data->tokens))
		return (false);
	if (!check_infile(data->tokens) || !check_delimiter(data->tokens))
		return (false);
	if (!check_cmd(data->tokens))
		return (false);
	if (!check_open(data->tokens))
		return (false);
	if (!check_access(data))
		return (false);
	clean_tokens = phoenix(&data->tokens);
	if (!clean_tokens)
		return (false);
	free_tokens(data->tokens);
	data->tokens = clean_tokens;
	//print_token_list(data->tokens);
	return (true);
}

bool	check_pipe(t_token *tokens)
{
	t_token	*tmp;

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

bool	check_outfile(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == REDIR_OUT)
		{
			if (tmp->next == NULL)
			{
				ft_printf("Missing file after redirection operator\n");
				return (false);
			}
			if (tmp->next->type != ARG)
			{
				ft_printf("Expected filename after redirection\n");
				return (false);
			}
			tmp = tmp->next;
			tmp->type = OUTFILE;
		}
		tmp = tmp->next;
	}
	return (true);
}

void	free_tab(char **str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	if (!str[i])
	{
		free(str);
		return ;
	}
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
