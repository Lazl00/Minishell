/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcournoy <lcournoy@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-15 14:28:21 by lcournoy          #+#    #+#             */
/*   Updated: 2025/05/22 15:01:49 by lcournoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_pwd(t_data *data, t_token *token)
{
	char	*pwd;
	int		fd;

	if (!data || !data->tokens)
		return (false);
	if (token->next && token->next->type == ARG)
		return (print_error("pwd"));
	fd = find_outfile_fd(token);
	if (fd < 0)
		return (false);
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		perror("getcwd");
		return (false);
	}
	ft_putstr_fd(pwd, fd);
	ft_putchar_fd('\n', fd);
	free(pwd);
	if (fd != STDOUT_FILENO)
		close(fd);
	return (true);
}
