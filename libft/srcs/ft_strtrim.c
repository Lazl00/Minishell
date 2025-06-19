/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 14:53:18 by wailas            #+#    #+#             */
/*   Updated: 2025/06/17 15:31:29 by wailas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static char	is_in_set(char const *s1, char c)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0')
	{
		if (s1[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char *s1, char *set)
{
	char	*res;
	int		start;
	int		end;
	int		i;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && is_in_set(set, s1[start]))
		start++;
	end = len(s1) - 1;
	while (end >= start && is_in_set(set, s1[end]))
		end--;
	res = malloc(end - start + 2);
	if (!res)
		return (NULL);
	i = -1;
	while (++i + start <= end)
		res[i] = s1[i + start];
	res[i] = '\0';
	free(s1);
	return (res);
}
