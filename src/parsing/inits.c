/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 10:00:00 by wailas            #+#    #+#             */
/*   Updated: 2025/05/07 14:19:01 by wailas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**make_env(char **env)
{
	int		i;
	int		len;
	char	**new_env;

	len = 0;
	while (env[len])
		len++;
	new_env = (char **)malloc((len + 1) * sizeof(char *));
	if (!new_env)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_env[i] = strdup(env[i]);
		if (!new_env[i])
		{
			while (--i >= 0)
				free(new_env[i]);
			free(new_env);
			return (NULL);
		}
		i++;
	}
	new_env[len] = NULL;
	return (new_env);
}

t_data	init_data(char **env)
{
	t_data	data;

	data.env = make_env(env);
	data.tokens = NULL;
	data.fd[0] = -1;
	data.fd[1] = -1;
	data.path = get_path(data.env);
	return (data);
}