/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 14:23:50 by wailas            #+#    #+#             */
/*   Updated: 2025/04/30 16:13:18 by wailas           ###   ########.fr       */
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

char	*ft_substr(char const *s, unsigned int start, size_t lenght)
{
	size_t	i;
	char	*result;
	int		taille;

	taille = ft_max((len(s) - start), 0);
	if (lenght >= (size_t)taille)
		lenght = taille;
	result = malloc(sizeof(char) * (ft_min(taille, lenght) + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (i < ft_min(taille, lenght))
	{
		result[i] = s[start + i];
		i++;
	}
	result[ft_min(taille, lenght)] = '\0';
	return (result);
}
