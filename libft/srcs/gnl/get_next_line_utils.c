/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:35:07 by wailas            #+#    #+#             */
/*   Updated: 2025/06/20 11:38:34 by wailas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/get_next_line.h"

char	*get_next_line(int fd, int flag)
{
	static char	*buf;
	char		*line;
	char		*tmp;

	clear_gnl_buffer(&buf, flag);
	if (fd == -1)
	{
		clear_gnl_buffer(&buf, 1);
		return (NULL);
	}
	buf = handle(fd, &buf);
	if (!buf)
		return (NULL);
	buf_manager(buf);
	line = ft_ligne(buf);
	if (!line)
	{
		clear_gnl_buffer(&buf, 1);
		return (NULL);
	}
	tmp = buf;
	buf = update_buffer(buf);
	buf_manager(buf);
	free(tmp);
	return (line);
}

void	buf_manager(char	*new_val)
{
	static char	*buf;

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
