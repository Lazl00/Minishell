/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcournoy <lcournoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 18:33:37 by wailas            #+#    #+#             */
/*   Updated: 2025/04/28 18:22:23 by lcournoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	valid_quotes(char *line)
{
	bool	single_quote;
	bool	double_quote;
	int		i;

	i = -1;
	single_quote = 0;
	double_quote = 0;
	while (line[++i])
	{
		if (line[i] == '\'' && double_quote == 0)
		{
			if (single_quote == 1)
				single_quote = 0;
			else
				single_quote = 1;
		}
		if (line[i] == '\"' && single_quote == 0)
		{
			if (double_quote == 1)
				double_quote = 0;
			else
				double_quote = 1;
		}
	}
	return (!(single_quote || double_quote));
}

bool	check_quote_state(char *line, int pos, char c)
{
	int		i;
	bool	single_quote;
	bool	double_quote;

	single_quote = false;
	double_quote = false;
	i = -1;
	while (++i <= pos)
	{
		if (line[i] == '\'' && double_quote == 0)
		{
			if (single_quote && i == pos)
				return (true);
			single_quote = !single_quote;
		}
		if (line[i] == '"' && single_quote == 0)
		{
			if (double_quote && i == pos)
				return (true);
			double_quote = !double_quote;
		}
	}
	if (c == '\'')
		return (single_quote);
	return (double_quote);
}

char	*quotes_remover(char *line)
{
	int		i;
	int		j;
	char	*final_line;

	i = 0;
	j = 0;
	final_line = malloc(len(line) - quote_counter(line) + 1);
	while (line[i])
	{
		if (line[i] == '\'' && check_quote_state(line, i, '\''))
			i++;
		else if (line[i] == '\"' && check_quote_state(line, i, '\"'))
			i++;
		else
			final_line[j++] = line[i++];
	}
	final_line[j] = '\0';
	free (line);
	return (final_line);
}

int	quote_counter(char *line)
{
	int	total;
	int	i;

	total = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' && check_quote_state(line, i, '\''))
			total++;
		else if (line[i] == '\"' && check_quote_state(line, i, '\"'))
			total++;
		i++;
	}
	return (total);
}

bool    in_any_quote(char *line, int pos)
{
    return(check_quote_state(line, pos, '\'') || check_quote_state(line, pos, '\"'));
}