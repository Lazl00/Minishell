/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 14:47:00 by lcournoy          #+#    #+#             */
/*   Updated: 2025/05/27 11:50:31 by wailas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_display(t_token *curr, int fd)
{
	while (curr && curr->type == ARG)
	{
		ft_putstr_fd(curr->value, fd);
		if (curr->next && curr->next->type == ARG)
			ft_putchar_fd(' ', fd);
		curr = curr->next;
	}
}

bool	ft_echo(t_data *data, t_token *token)
{
	int		fd;
	bool	new_line;
	t_token	*curr;

	fd = STDOUT_FILENO;
	new_line = true;
	curr = token->next;
	if (!data || !token)
		return (false);
	while (curr && curr->type == ARG && ft_strncmp(curr->value, "-n", 3) == 0)
	{
		new_line = false;
		curr = curr->next;
	}
	fd = find_outfile_fd(token);
	if (fd < 0)
		return (false);
	ft_display(curr, fd);
	if (new_line)
		ft_putchar_fd('\n', fd);
	if (fd != STDOUT_FILENO)
		close(fd);
	return (true);
}
