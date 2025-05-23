/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 10:00:00 by wailas            #+#    #+#             */
/*   Updated: 2025/05/14 18:07:00 by wailas           ###   ########.fr       */
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
		new_env[i] = ft_strdup(env[i]);
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

t_data	*init_data(t_data *data, char **env)
{
	(*data).env = make_env(env);
	(*data).tokens = NULL;
	(*data).fd[0] = -1;
	(*data).fd[1] = -1;
	(*data).exit_status = 0;
	return (data);
}

void	print_str_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		printf("%s\n", arr[i]);
		i++;
	}
}
