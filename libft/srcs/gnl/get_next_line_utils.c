/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidailas <walidailas@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:35:07 by wailas            #+#    #+#             */
/*   Updated: 2025/02/05 16:39:42 by walidailas       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/get_next_line.h"

void	buf_manager(char	*new_val)
{
	static char *buf;

	if (new_val == NULL)
	{
		free(buf);
		buf = NULL;
	}
	else
		buf = new_val;
}

int	ft_found(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str && str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

void	clear_gnl_buffer(char **buf, int flag)
{
	if (flag == 1 || *buf == NULL)
	{
		free(*buf);
		*buf = NULL;
	}
}
