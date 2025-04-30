/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:02:36 by wailas            #+#    #+#             */
/*   Updated: 2025/04/30 16:54:52 by wailas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strtok(char *str, const char *delim)
{
	static char	*last;
	char		*start;
	int			in_single_quote = 0;
	int			in_double_quote = 0;

	if (str)
		last = str;
	if (!last)
		return (NULL);
	while (*last && ft_strchr(delim, *last))
		last++;
	if (*last == '\0')
		return (NULL);

	start = last;
	while (*last)
	{
		if (*last == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (*last == '\"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		else if (ft_strchr(delim, *last) && !in_single_quote && !in_double_quote)
			break;
		last++;
	}
	if (*last)
	{
		*last = '\0';
		last++;
	}
	return (start);
}
