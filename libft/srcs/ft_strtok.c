/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:02:36 by wailas            #+#    #+#             */
/*   Updated: 2025/04/08 16:02:56 by wailas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strtok(char *str, const char *delim)
{
	static char	*last = NULL;
	char		*start;

	if (str != NULL)
		last = str;
	if (last == NULL)
		return (NULL);
	while (*last && ft_strchr(delim, *last))
		last++;
	if (*last == '\0')
		return (NULL);
	start = last;
	while (*last && !ft_strchr(delim, *last))
		last++;
	if (*last)
	{
		*last = '\0';
		last++;
	}
	return (start);
}
