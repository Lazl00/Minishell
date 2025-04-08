/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 12:01:52 by wailas            #+#    #+#             */
/*   Updated: 2024/11/15 12:37:56 by wailas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*liste;

	liste = malloc(sizeof(*liste));
	if (liste == NULL)
		return (NULL);
	liste->content = content;
	liste->next = NULL;
	return (liste);
}
