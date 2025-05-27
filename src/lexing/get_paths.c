/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:20:44 by lcournoy          #+#    #+#             */
/*   Updated: 2025/05/27 13:30:42 by wailas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**get_paths_from_env(char **env)
{
	int		i;

	if (!env)
		return (NULL);
	i = 0;
	while (env[i] && ft_strnstr(env[i], "PATH=", 5) == 0)
		i++;
	if (!env[i])
		return (NULL);
	return (ft_split(env[i] + 5, ':'));
}

char	*construct_path(char *dir, char *command)
{
	char	*cut_path;
	char	*full_path;

	cut_path = ft_strjoin(dir, "/");
	if (!cut_path)
		return (NULL);
	full_path = ft_strjoin(cut_path, command);
	free(cut_path);
	return (full_path);
}

static char	*search_in_paths(char **paths, char *command)
{
	int		i;
	char	*reel_path;

	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		reel_path = construct_path(paths[i], command);
		if (access(reel_path, F_OK) == 0)
		{
			free_tab(paths);
			return (reel_path);
		}
		free(reel_path);
		i++;
	}
	free_tab(paths);
	return (NULL);
}

char	*get_path(char *command, char **env)
{
	char	**paths;

	if (!command || !command[0])
		return (NULL);
	if (access(command, F_OK) == 0)
		return (ft_strdup(command));
	if (!env)
		return (NULL);
	paths = get_paths_from_env(env);
	if (!paths)
		return (NULL);
	return (search_in_paths(paths, command));
}

char	*check_exec(t_token *token, char **env)
{
	char	*path;

	if (!token || !token->value)
		return (NULL);
	if (ft_strncmp(token->value, "./", 2) == 0 || \
			ft_strncmp(token->value, "/", 1) == 0)
	{
		return (ft_strdup(token->value));
	}
	path = get_path(token->value, env);
	if (!path)
	{
		ft_printf("command not found : %s\n", token->value);
		return (ft_strdup(token->value));
	}
	return (path);
}
