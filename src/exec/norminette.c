/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norminette.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcournoy <lcournoy@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-20 10:06:26 by lcournoy          #+#    #+#             */
/*   Updated: 2025/06/20 12:10:13 by lcournoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	norminette_hd(t_data *data, int write_fd)
{
	exit_hdoc(data);
	exit_pipe(write_fd);
	signal(SIGINT, sigint_handler_heredoc);
	signal(SIGQUIT, SIG_IGN);
}

void	norminette_hd2(void)
{
	write(2, "\n", 2);
	exit_str(NULL, 0);
}

void	exit_fd(void *fill)
{
	int	fd;

	(void)fill;
	fd = 3;
	while (fd < 1024)
	{
		close(fd);
		fd++;
	}
}
