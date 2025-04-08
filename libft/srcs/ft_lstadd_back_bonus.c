/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:48:06 by wailas            #+#    #+#             */
/*   Updated: 2024/11/15 16:08:40 by wailas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_lstadd_back(t_list **lst, t_list *lst2)
{
	t_list	*current;

	if (*lst == NULL)
		*lst = lst2;
	else
	{
		current = *lst;
		if (!current)
			current = lst2;
		while (current-> next != NULL)
			current = current-> next;
		current->next = lst2;
	}
}
