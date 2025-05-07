/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:15:00 by wailas            #+#    #+#             */
/*   Updated: 2025/05/07 15:19:09 by wailas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**get_paths_from_env(char **envp)
{
	int		i;

	if (!envp)
		return (NULL);
	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH=", 5) == 0)
		i++;
	if (!envp[i])
		return (NULL);
	return (ft_split(envp[i] + 5, ':'));
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

char	*get_path(char *command, char **envp)
{
	char	**paths;

	if (!command || !command[0])
		return (NULL);
	if (access(command, F_OK) == 0)
		return (ft_strdup(command));
	if (!envp)
		return (NULL);
	paths = get_paths_from_env(envp);
	if (!paths)
		return (NULL);
	return (search_in_paths(paths, command));
}