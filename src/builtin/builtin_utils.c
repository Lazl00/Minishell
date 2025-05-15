/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcournoy <lcournoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:49:04 by lcournoy          #+#    #+#             */
/*   Updated: 2025/05/15 15:21:48 by lcournoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_builtin(t_data *data)
{
	t_token	*tmp = data->tokens;

	if (!tmp || !tmp->value)
		return (false);

	if (ft_strncmp(tmp->value, "echo", 4) == 0)
		return (ft_echo(data, tmp));
	if (ft_strncmp(tmp->value, "cd", 2) == 0)
		return (ft_cd(data, tmp));
	if (ft_strncmp(tmp->value, "pwd", 3) == 0)
		return (ft_pwd(data, tmp));
	if (ft_strncmp(tmp->value, "export", 6) == 0)
		return (ft_export(data, tmp));
	if (ft_strncmp(tmp->value, "unset", 5) == 0)
		return (ft_unset(data, tmp));
	if (ft_strncmp(tmp->value, "env", 3) == 0)
		return (ft_env(data, tmp));
	// if (ft_strncmp(tmp->value, "exit", 4) == 0)
	// 	return (ft_exit(data, tmp));

	return (false);
}
