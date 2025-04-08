/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 11:43:37 by wailas            #+#    #+#             */
/*   Updated: 2024/12/26 11:50:24 by wailas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/get_next_line_bonus.h"

char	*read_line(int fd, char *str)
{
	char	*buffer;
	int		read_bytes;
	int		found_newline;
	char	*temp;

	found_newline = 0;
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!str)
		str = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	while (!found_newline)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
			return (free(str), free(buffer), NULL);
		if (read_bytes == 0)
			break ;
		buffer[read_bytes] = 0;
		temp = str;
		str = ft_strjoin(str, buffer);
		free(temp);
		if (ft_found2(buffer) != -1)
			found_newline = 1;
	}
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
	str = ft_calloc(ft_strlen(buffer) - i + 1, sizeof(char));
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
	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (fd >= 0 && fd < OPEN_MAX && buffer[fd])
		{
			free(buffer[fd]);
			buffer[fd] = NULL;
		}
		return (NULL);
	}
	buffer[fd] = read_line(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	return (buffer[fd]);
}

char	*get_next_line(int fd)
{
	static char	*buffer[OPEN_MAX];
	char		*line;
	char		*temp;

	if (!handle(fd, buffer))
		return (NULL);
	line = ft_ligne(buffer[fd]);
	if (!line)
	{
		free(buffer[fd]);
		return (buffer[fd] = NULL);
	}
	temp = buffer[fd];
	buffer[fd] = update_buffer(buffer[fd]);
	free(temp);
	return (line);
}
