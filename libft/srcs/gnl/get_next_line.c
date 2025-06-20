/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcournoy <lcournoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:35:05 by wailas            #+#    #+#             */
/*   Updated: 2025/04/24 18:10:36 by lcournoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/get_next_line.h"
#include "../../include/libft.h"
\

char	*read_line(int fd, char *str)
{
	char	*buffer;
	char	*temp;
	ssize_t	read_bytes;

	buffer = malloc(BUFFER_SIZE + 1);
	exit_buffer(buffer);
	if (!buffer)
		return (free(str), NULL);
	if (!str)
	{
		str = ft_calloc(1, sizeof(char));
		exit_str(str, 0);
		if (!str)
			return (free(buffer), NULL);
	}
	while (1)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes <= 0)
			break ;
		buffer[read_bytes] = '\0';
		temp = str;
		str = ft_strjoin(str, buffer);
		free(temp);
		if (ft_found(buffer) != -1)
			break ;
	}
	free(buffer);
	if (read_bytes == -1 || !str || !*str)
		return (NULL);
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
