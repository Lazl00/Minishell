/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:28:26 by lcournoy          #+#    #+#             */
/*   Updated: 2025/05/27 11:55:38 by wailas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_add_or_delete(t_data *data, char **new_env, int *k)
{
	int		i;
	size_t	ft_strlen;

	i = 0;
	while (data->env[i])
	{
		ft_strlen = len(data->tokens->next->value);
		if (ft_strncmp(data->env[i], data->tokens->next->value, ft_strlen) == 0
			&& data->env[i][ft_strlen] == '=')
			free(data->env[i]);
		else
		{
			new_env[*k] = data->env[i];
			(*k)++;
		}
		i++;
	}
}

bool	ft_unset(t_data *data, t_token *token)
{
	int		i;
	int		k;
	char	**new_env;

	if (!data || !data->env || !token->next)
		return (false);
	i = 0;
	while (data->env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 1));
	if (!new_env)
		return (false);
	k = 0;
	ft_add_or_delete(data, new_env, &k);
	new_env[k] = NULL;
	free(data->env);
	data->env = new_env;
	return (true);
}
