/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:49:04 by lcournoy          #+#    #+#             */
/*   Updated: 2025/05/22 15:01:12 by lcournoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_builtin(t_token *token)
{
	if (!token || !token->value)
		return (false);
	if (ft_strcmp(token->value, "echo") == 0)
		return (true);
	if (ft_strcmp(token->value, "cd") == 0)
		return (true);
	if (ft_strcmp(token->value, "pwd") == 0)
		return (true);
	if (ft_strcmp(token->value, "export") == 0)
		return (true);
	if (ft_strcmp(token->value, "unset") == 0)
		return (true);
	if (ft_strcmp(token->value, "env") == 0)
		return (true);
	if (ft_strcmp(token->value, "exit") == 0)
		return (true);
	return (false);
}

int	do_builtin(t_data *data, t_token *token)
{
	int	exit;

	exit = false;
	if (ft_strncmp(token->value, "echo", len(token->value)) == 0)
		exit = ft_echo(data, token);
	if (ft_strncmp(token->value, "cd", len(token->value)) == 0)
		exit = ft_cd(data, token);
	if (ft_strncmp(token->value, "pwd", len(token->value)) == 0)
		exit = ft_pwd(data, token);
	if (ft_strncmp(token->value, "export", len(token->value)) == 0)
		exit = ft_export(data, token);
	if (ft_strncmp(token->value, "unset", len(token->value)) == 0)
		exit = ft_unset(data, token);
	if (ft_strncmp(token->value, "env", len(token->value)) == 0)
		exit = ft_env(data, token);
	if (ft_strncmp(token->value, "exit", len(token->value)) == 0)
		exit = ft_exit(data, token);
	if (exit != 127)
		return (!exit);
	return (exit);
}
