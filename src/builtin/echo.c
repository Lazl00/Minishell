/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcournoy <lcournoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 14:47:00 by lcournoy          #+#    #+#             */
/*   Updated: 2025/05/22 14:56:59 by lcournoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	while (curr && curr->type == ARG)
	{
		ft_putstr_fd(curr->value, fd);
		if (curr->next && curr->next->type == ARG)
			ft_putchar_fd(' ', fd);
		curr = curr->next;
	}
	if (new_line)
		ft_putchar_fd('\n', fd);
	if (fd != STDOUT_FILENO)
		close(fd);
	return (true);
}
