/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 11:52:10 by wailas            #+#    #+#             */
/*   Updated: 2025/04/30 16:12:45 by wailas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static char	*get_string(char const *str, int length)
{
	char	*array;

	array = malloc(sizeof(char) * (length + 1));
	if (!array)
		return (NULL);
	ft_strlcpy(array, str, length + 1);
	array[length] = '\0';
	return (array);
}

static int	countwords(const char *str, char c)
{
	int	count;
	int	in_words;

	in_words = 0;
	count = 0;
	while (*str)
	{
		if (*str != c && in_words == 0)
		{
			in_words = 1;
			count++;
		}
		else if (*str == c)
			in_words = 0;
		str++;
	}
	return (count);
}

static char	**ft_split2(char const *s, char c, char **array)
{
	int	element;
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			element = 0;
			while (s[i + element] != c && s[i + element])
				element++;
			array[j++] = get_string(s + i, element);
			i += element;
		}
		else
			i++;
	}
	array[j] = NULL;
	return (array);
}

char	**ft_split(char const *s, char c)
{
	char	**array;

	if (!s)
		return (NULL);
	array = (char **)malloc(sizeof(char *) * (countwords(s, c) + 1));
	if (!array)
		return (NULL);
	return (ft_split2(s, c, array));
}
