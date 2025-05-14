/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   accesses.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:36:38 by wailas            #+#    #+#             */
/*   Updated: 2025/05/14 16:52:23 by wailas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>

bool check_open(t_token *tokens)
{
	t_token *tmp = tokens;
	int		fd;

	while (tmp)
	{
		if (tmp->type == INFILE)
		{
			fd = open(tmp->value, O_RDONLY);
			if (fd < 0)
			{
				perror(tmp->value);
				return (false);
			}
			close(fd);
		}
		else if (tmp->type == OUTFILE || tmp->type == APPEND_FILE)
        {
			check_file(tmp, fd);
            close(fd);
        }
        tmp = tmp->next;
	}
	return (true);
}

void    check_file(t_token *token, int fd)
{
		if (token->type == OUTFILE)
        {
			fd = open(token->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
				perror(token->value);
			close(fd);
		}
		else if (token->type == APPEND_FILE)
		{
			fd = open(token->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd < 0)
				perror(token->value);
			close(fd);
		}
}
