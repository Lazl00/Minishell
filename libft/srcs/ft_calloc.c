/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 11:44:50 by wailas            #+#    #+#             */
/*   Updated: 2025/01/09 11:31:48 by wailas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t		i;
	char		*total;
	size_t		taille;

	taille = nmemb * size;
	total = malloc(taille);
	if (total == NULL)
		return (NULL);
	i = 0;
	while (i < taille)
	{
		total[i] = 0;
		i++;
	}
	return (total);
}
