/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcournoy <lcournoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 18:48:25 by wailas            #+#    #+#             */
/*   Updated: 2025/06/20 01:56:16 by lcournoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens->next;
		free(tokens->value);
		free(tokens);
		tokens = tmp;
	}
}

void	free_data(t_data *data)
{
	int	i;

	if (!data)
		return ;
	if (data->tokens)
		free_tokens(data->tokens);
	if (data->env)
	{
		i = 0;
		while (data->env[i])
			free(data->env[i++]);
		free(data->env);
	}
	free(data);
}

void	free_data_main(t_data *data)
{
	int	i;

	if (!data)
		return ;
	if (data->env)
	{
		i = 0;
		while (data->env[i])
			free(data->env[i++]);
		free(data->env);
	}
	free(data);
}

char	*read_loop(int fd, char *buf, char *str)
{
	char	*tmp;
	ssize_t	r;

	while ((r = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[r] = '\0';
		tmp = str;
		str = ft_strjoin(str, buf);
		free(tmp);
		if (ft_found(buf) != -1)
			break ;
	}
	if (r == -1 || !str || !*str)
		return (free(str), NULL);
	return (str);
}
char	*init_str(char *str, char *buffer)
{
	if (!str)
	{
		str = ft_calloc(1, sizeof(char));
		exit_str(str, 0);
		if (!str)
		{
			free(buffer);
			return (NULL);
		}
	}
	return (str);
}