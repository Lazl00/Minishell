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
	size_t	lenght;

	i = 0;
	while (data->env[i])
	{
		lenght = len(data->tokens->next->value);
		if (ft_strncmp(data->env[i], data->tokens->next->value, lenght) == 0
			&& data->env[i][lenght] == '=')
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

	if (!data || !data->env)
		return (false);
	if (!token->next)
		return (true);
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
