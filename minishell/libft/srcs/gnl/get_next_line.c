/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:35:05 by wailas            #+#    #+#             */
/*   Updated: 2024/12/26 13:17:59 by wailas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/get_next_line.h"
#include "../../include/libft.h"
#define GNL_CLEAR 1
#define GNL_KEEP 0

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
		if (ft_found(buffer) != -1)
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
		clear_gnl_buffer(&buf, GNL_CLEAR);
		return (NULL);
	}
	buf = handle(fd, &buf);
	if (!buf)
		return (NULL);
	line = ft_ligne(buf);
	if (!line)
	{
		clear_gnl_buffer(&buf, GNL_CLEAR);
		return (NULL);
	}
	tmp = buf;
	buf = update_buffer(buf);
	free(tmp);
	return (line);
}

/*int	main(int ac, char **av)
 {
	int			fd;
	char		*line;
	int			i = 0;

	if (ac != 2)
		write(1, "y'a une erreur frerot", 21);
	fd = open(av[1], O_RDWR);
	if (fd == -1)
		return (1);
	while ((i < 4))
	{
		line = get_next_line(fd);
		printf("%s", line);
		free(line);
		i++;
	}
	close(fd);
	return (0);
}*/
