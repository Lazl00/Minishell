/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 18:17:42 by wailas            #+#    #+#             */
/*   Updated: 2025/05/27 11:54:36 by wailas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	find_outfile_fd(t_token *cmd)
{
	t_token	*tmp;
	t_token	*last_out;

	tmp = cmd;
	last_out = NULL;
	while (tmp)
	{
		if (tmp->type == OUTFILE || tmp->type == APPEND_FILE)
			last_out = tmp;
		else if (tmp->type == PIPE)
			return (STDOUT_FILENO);
		tmp = tmp->next;
	}
	if (!last_out)
		return (STDOUT_FILENO);
	if (last_out->type == OUTFILE)
		return (open(last_out->value, O_WRONLY | O_CREAT | O_TRUNC, 0644));
	else
		return (open(last_out->value, O_WRONLY | O_CREAT | O_APPEND, 0644));
	return (STDOUT_FILENO);
}

bool	ft_env(t_data *data, t_token *cmd)
{
	int		i;
	int		fd;

	i = 0;
	if (!data || !data->env)
		return (false);
	if (cmd->next && cmd->next->type == ARG)
		return (print_error("env: too many arguments"));
	fd = find_outfile_fd(cmd);
	if (fd < 0)
		return (false);
	while (data->env[i])
	{
		ft_putstr_fd(data->env[i], fd);
		ft_putchar_fd('\n', fd);
		i++;
	}
	if (fd != STDOUT_FILENO)
		close(fd);
	return (true);
}
