/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:35:05 by wailas            #+#    #+#             */
/*   Updated: 2025/06/20 11:39:44 by wailas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/get_next_line.h"
#include "../../include/libft.h"

static char	*read_line_loop(int fd, char *buffer, char *str)
{
	ssize_t	read_bytes;
	char	*temp;

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

char	*read_line(int fd, char *str)
{
	char	*buffer;

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
	return (read_line_loop(fd, buffer, str));
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

char	*handle(int fd, char **buffer)
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
