/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:49:04 by lcournoy          #+#    #+#             */
/*   Updated: 2025/05/15 19:13:16 by wailas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_builtin(t_token *token)
{
	if (!token || !token->value)
		return (false);
	if (ft_strncmp(token->value, "echo", len(token->value)) == 0)
		return (true);
	if (ft_strncmp(token->value, "cd", len(token->value)) == 0)
		return (true);
	if (ft_strncmp(token->value, "pwd", len(token->value)) == 0)
		return (true);
	if (ft_strncmp(token->value, "export", len(token->value)) == 0)
		return (true);
	if (ft_strncmp(token->value, "unset", len(token->value)) == 0)
		return (true);
	if (ft_strncmp(token->value, "env", len(token->value)) == 0)
		return (true);
	if (ft_strncmp(token->value, "exit", len(token->value)) == 0)
		return (true);
	return (false);
}