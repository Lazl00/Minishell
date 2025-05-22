/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcournoy <lcournoy@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-15 14:28:26 by lcournoy          #+#    #+#             */
/*   Updated: 2025/05/22 15:00:42 by lcournoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_unset(t_data *data, t_token *token)
{
	int		i;
	int		k;
	char	**new_env;

	i = 0;
	k = 0;
	if (!data || !data->env || !token->next)
		return (false);
	while (data->env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 1));
	if (!new_env)
		return (false);
	i = 0;
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], token->next->value, \
					len(token->next->value)) == 0 \
				&& data->env[i][len(token->next->value)] == '=')
			free(data->env[i]);
		else
			new_env[k++] = data->env[i];
		i++;
	}
	new_env[k] = NULL;
	free(data->env);
	data->env = new_env;
	return (true);
}
