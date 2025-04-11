/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 18:33:37 by wailas            #+#    #+#             */
/*   Updated: 2025/04/11 18:35:33 by wailas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*handle_quotes(const char *str)
{
	int				i;
	int				j;
	t_enum_quote	state;
	char			*result;

	i = 0;
	j = 0;
	state = outside;
	result = malloc(ft_strlen(str) * (2 + 1));
	if (!result)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\'' && state == outside)
			state = inside_single_quote;
		else if (str[i] == '\'' && state == inside_single_quote)
			state = outside;
		else if (str[i] == '\"' && state == outside)
			state = inside_double_quote;
		else if (str[i] == '\"' && state == inside_double_quote)
			state = outside;
		if (str[i] == ' ' && state != outside)
			result[j++] = 1;
		else
			result[j++] = str[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}
