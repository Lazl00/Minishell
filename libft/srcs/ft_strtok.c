/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcournoy <lcournoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:02:36 by wailas            #+#    #+#             */
/*   Updated: 2025/04/30 17:12:25 by lcournoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*get_token_end(char *s, const char *delim)
{
	int	single_quote;
	int	double_quote;

	single_quote = 0;
	double_quote = 0;
	while (*s)
	{
		if (*s == '\'' && !double_quote)
			single_quote = !single_quote;
		else if (*s == '\"' && !single_quote)
			double_quote = !double_quote;
		else if (ft_strchr(delim, *s) && !single_quote && !double_quote)
			break ;
		s++;
	}
	return (s);
}

char	*ft_strtok(char *str, const char *delim)
{
	static char	*last;
	char		*start;

	if (str)
		last = str;
	if (!last)
		return (NULL);
	while (*last && ft_strchr(delim, *last))
		last++;
	if (*last == '\0')
		return (NULL);
	start = last;
	last = get_token_end(last, delim);
	if (*last)
	{
		*last = '\0';
		last++;
	}
	return (start);
}
