/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:27:14 by lcournoy          #+#    #+#             */
/*   Updated: 2025/05/27 11:47:48 by wailas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_cd_home(char *oldpwd)
{
	char	*home;

	home = getenv("HOME");
	if (!home)
	{
		ft_putendl_fd("cd: HOME not set", 2);
		free(oldpwd);
		return (false);
	}
	if (chdir(home) == -1)
		perror("cd");
	free(oldpwd);
	return (true);
}

bool	ft_cd_oldpwd(char *oldpwd)
{
	char	*oldpwd_env;

	oldpwd_env = getenv("OLDPWD");
	if (!oldpwd_env)
	{
		ft_putendl_fd("cd: OLDPWD not set", 2);
		free(oldpwd);
		return (false);
	}
	if (chdir(oldpwd_env) == -1)
		perror("cd");
	else
		printf("%s\n", oldpwd_env);
	free(oldpwd);
	return (true);
}

bool	ft_cd(t_data *data, t_token *token)
{
	char	*oldpwd;
	char	*target;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		return (false);
	if (!token->next || !token->next->value)
		return (ft_cd_home(oldpwd));
	target = token->next->value;
	if (ft_strcmp(target, "~") == 0)
		return (ft_cd_home(oldpwd));
	if (ft_strcmp(target, "-") == 0)
		return (ft_cd_oldpwd(oldpwd));
	if (chdir(target) == -1)
		perror("cd");
	update_pwd_env(data, oldpwd);
	free(oldpwd);
	return (true);
}

bool	update_pwd_env(t_data *data, char *oldpwd)
{
	char	*newpwd;

	newpwd = getcwd(NULL, 0);
	if (!newpwd)
	{
		perror("getcwd");
		return (false);
	}
	ft_replace_env(data, "OLDPWD", oldpwd);
	ft_replace_env(data, "PWD", newpwd);
	free(newpwd);
	return (true);
}

void	ft_replace_env(t_data *data, char *var, char *value)
{
	int		i;
	char	*new_var;

	i = 0;
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], var, len(var)) == 0 \
				&& data->env[i][len(var)] == '=')
		{
			free(data->env[i]);
			new_var = malloc(sizeof(char) * (len(var) + len(value) + 2));
			if (!new_var)
				return ;
			sprintf(new_var, "%s=%s", var, value);
			data->env[i] = new_var;
			return ;
		}
		i++;
	}
}
