/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcournoy <lcournoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:20:44 by lcournoy          #+#    #+#             */
/*   Updated: 2025/04/16 17:58:10 by lcournoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_path(char **envp)
{
	char	*path;

	path = ft_getenv("PATH", envp);
	return (path);
}

char	*ft_getenv(char *str, char **envp)
{
	int		i;
	int		j;
	char	*sub;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] && envp[i][j] != '=')
			j++;
		sub = ft_substr(envp[i], 0, j);
		if (ft_strncmp(sub, str, ft_strlen(sub)) == 0)
		{
			free(sub);
			return (&envp[i][j + 1]);
		}
		free(sub);
		i++;
	}
	return (NULL);
}