/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 14:23:50 by wailas            #+#    #+#             */
/*   Updated: 2025/01/09 11:33:14 by wailas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static unsigned long	ft_max(long x, long y)
{
	if (x > y)
		return (x);
	else
		return (y);
}

static unsigned long	ft_min(long x, long y)
{
	if (x < y)
		return (x);
	else
		return (y);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*result;
	int		taille;

	taille = ft_max((ft_strlen(s) - start), 0);
	if (len >= (size_t)taille)
		len = taille;
	result = malloc(sizeof(char) * (ft_min(taille, len) + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (i < ft_min(taille, len))
	{
		result[i] = s[start + i];
		i++;
	}
	result[ft_min(taille, len)] = '\0';
	return (result);
}
