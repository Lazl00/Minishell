/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:20:44 by lcournoy          #+#    #+#             */
/*   Updated: 2025/05/14 17:44:54 by wailas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// char	*get_path(char **envp)
// {
// 	char	*path;

// 	path = ft_getenv("PATH", envp);
// 	return (path);
// }

// char	*ft_getenv(char *str, char **envp)
// {
// 	int		i;
// 	int		j;
// 	char	*sub;

// 	i = 0;
// 	while (envp[i])
// 	{
// 		j = 0;
// 		while (envp[i][j] && envp[i][j] != '=')
// 			j++;
// 		sub = ft_substr(envp[i], 0, j);
// 		if (ft_strncmp(sub, str, len(sub)) == 0)
// 		{
// 			free(sub);
// 			return (&envp[i][j + 1]);
// 		}
// 		free(sub);
// 		i++;
// 	}
// 	return (NULL);
// }

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

bool	exec(t_token *token, char **env)
{
	char	*path;
	char	**path_command;

	path_command = ft_split(token->value, ' ');
	if (!path_command || !path_command[0])
	{
		perror("Invalid command\n");
		free_tab(path_command);
		return (true);
	}
	if (access(path_command[0], F_OK) == 0)
		path = ft_strdup(path_command[0]);
	else
		path = get_path(path_command[0], env);
	if (!path)
		return (free_tab(path_command), perror("Command not found\n"), true);
	free(path);
	return (false);
}

void	free_tab(char **str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
