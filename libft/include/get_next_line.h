/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcournoy <lcournoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:35:09 by wailas            #+#    #+#             */
/*   Updated: 2025/06/20 01:57:26 by lcournoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdio.h>
# include "libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

/*	Fonction get_next_line	*/

size_t	len(const char *s);
char	*get_next_line(int fd, int flag);
char	*update_buffer(char *buffer);
int		ft_found(const char *str);
char	*ft_ligne(char *buffer);
void	*ft_calloc(size_t nmemb, size_t size);
void	clear_gnl_buffer(char **buf, int flag);

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*str_join_and_free(char *s1, const char *s2);
int		find_newline(const char *str);
void	buf_manager(char *str);
void	exit_str(char *line, int check);
void	exit_buffer(char *line);
char	*init_str(char *str, char *buffer);
char	*read_loop(int fd, char *buf, char *str);

#endif
