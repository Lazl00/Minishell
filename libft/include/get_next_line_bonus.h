/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 11:43:28 by wailas            #+#    #+#             */
/*   Updated: 2025/04/30 16:14:11 by wailas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include "libft.h"

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 42
# endif

/*	Fonction get_next_line	*/

size_t	len(const char *s);
char	*get_next_line(int fd);
//char	*ft_strjoin(char *s1, const char *s2);
char	*update_buffer(char *buffer);
int		ft_found2(const char *str);
char	*ft_ligne(char *buffer);
void	*ft_calloc(size_t nmemb, size_t size);

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*str_join_and_free(char *s1, const char *s2);
char	*get_next_line(int fd);
int		find_newline(const char *str);

#endif
