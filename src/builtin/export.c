/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:27:42 by lcournoy          #+#    #+#             */
/*   Updated: 2025/05/27 11:55:19 by wailas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_valid_identifier(const char *str)
{
	size_t	i;

	if (!str || (!isalpha(str[0]) && str[0] != '_'))
		return (false);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!isalnum(str[i]) && str[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

bool	ft_add(t_data *data, char *name, size_t name_len)
{
	int	i;

	i = 0;
	while (data->env[i])
	{
		if (!ft_strncmp(data->env[i], name, name_len)
			&& data->env[i][name_len] == '=')
		{
			free(data->env[i]);
			data->env[i] = ft_strdup(data->tokens->next->value);
			return (true);
		}
		i++;
	}
	return (false);
}

char	**ft_copy_env_and_add(t_data *data, char *value)
{
	char	**new_env;
	int		i;
	int		j;

	i = 0;
	while (data->env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return (NULL);
	j = 0;
	while (j < i)
	{
		new_env[j] = data->env[j];
		j++;
	}
	new_env[j] = ft_strdup(value);
	new_env[j + 1] = NULL;
	return (new_env);
}

bool	ft_export(t_data *data, t_token *token)
{
	char	**new_env;
	char	*name;
	size_t	name_len;

	if (!data || !data->env || !token || !token->next)
		return (false);
	if (!is_valid_identifier(token->next->value))
	{
		ft_putstr_fd("export: not a valid identifier\n", 2);
		return (false);
	}
	name = token->next->value;
	name_len = 0;
	while (name[name_len] && name[name_len] != '=')
		name_len++;
	if (name[name_len] != '=')
		return (true);
	if (ft_add(data, name, name_len))
		return (true);
	new_env = ft_copy_env_and_add(data, token->next->value);
	if (!new_env)
		return (false);
	free(data->env);
	data->env = new_env;
	return (true);
}
