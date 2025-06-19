/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcournoy <lcournoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:35:05 by wailas            #+#    #+#             */
/*   Updated: 2025/06/20 01:55:55 by lcournoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/get_next_line.h"
#include "../../include/libft.h"

char	*read_line(int fd, char *str)
{
	char	*buffer;

	buffer = malloc(BUFFER_SIZE + 1);
	exit_buffer(buffer);
	if (!buffer)
		return (free(str), NULL);
	str = init_str(str, buffer);
	if (!str)
		return (NULL);
	str = read_loop(fd, buffer, str);
	free(buffer);
	return (str);
}

char	*update_buffer(char *buffer)
{
	char	*str;
	int		i;
	int		j;

	if (!buffer || buffer[0] == '\0')
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	str = ft_calloc(len(buffer) - i + 1, sizeof(char));
	if (!str)
		return (NULL);
	j = 0;
	while (buffer[i])
		str[j++] = buffer[i++];
	str[j] = '\0';
	return (str);
}

char	*ft_ligne(char *buffer)
{
	int		i;
	char	*str;

	if (!buffer || buffer[0] == '\0')
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		str = ft_calloc(i + 2, sizeof(char));
	else
		str = ft_calloc(i + 1, sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		str[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		str[i++] = '\n';
	return (str);
}

static char	*handle(int fd, char **buffer)
{
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (*buffer)
		{
			free(*buffer);
			*buffer = NULL;
		}
		return (NULL);
	}
	*buffer = read_line(fd, *buffer);
	return (*buffer);
}

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
