/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigs_strat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcournoy <lcournoy@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-19 11:37:44 by lcournoy          #+#    #+#             */
/*   Updated: 2025/06/19 13:49:58 by lcournoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exit_line(char *line)
{
	static char	*backup;

	if (line)
		backup = line;
	else if (line == NULL && backup)
	{
		free(backup);
	}
}

void	exit_hdoc(t_data *data)
{
	static t_data	*backup;

	if (data)
		backup = data;
	else if (data == NULL && backup)
	{
		free_data(backup);
	}
}

void	exit_pipe(int fd)
{
	static int	backup = 42;

	if (fd != -1)
	{
		backup = fd;
	}
	else if (fd == -1 && backup != 42)
	{
		close(backup);
	}
}

void	exit_buffer(char *line)
{
	static char	*backup;

	if (line)
		backup = line;
	else if (line == NULL && backup)
	{
		free(backup);
		backup = NULL;
	}
}
void	exit_str(char *line, int check)
{
	static char	*backup;
	static char	flag;

	if (check == 1)
	{
		flag = 1;
		return ;
	}
	if (line)
		backup = line;
	else if (line == NULL && flag != 1)
	{
		free(backup);
		backup = NULL;
	}
}
