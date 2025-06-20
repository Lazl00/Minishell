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

bool	is_n_option(const char *str)
{
	if (!str || str[0] != '-' || str[1] != 'n')
		return (false);
	for (int i = 2; str[i]; i++)
	{
		if (str[i] != 'n')
			return (false);
	}
	return (true);
}

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
		bool	new_line;
	t_token	*curr;

	new_line = true;
	curr = token->next;
	if (!data || !token)
		return (false);
	while (curr && curr->type == ARG && is_n_option(curr->value))
	{
		new_line = false;
		curr = curr->next;
	}
	ft_display(curr, find_outfile_fd(token));
	if (new_line)
		ft_putchar_fd('\n', find_outfile_fd(token));
	if (find_outfile_fd(token) != STDOUT_FILENO)
		close(find_outfile_fd(token));
	return (true);
}
