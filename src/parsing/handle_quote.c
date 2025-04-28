/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 18:33:37 by wailas            #+#    #+#             */
/*   Updated: 2025/04/28 16:29:47 by wailas           ###   ########.fr       */
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
