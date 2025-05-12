/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcournoy <lcournoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 18:48:25 by wailas            #+#    #+#             */
/*   Updated: 2025/05/12 15:55:20 by lcournoy         ###   ########.fr       */
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

	if (data)
	{
		if (data->env)
		{
			i = 0;
			while (data->env[i])
			{
				free(data->env[i]);
				i++;
			}
			free(data->env);
		}
		//free(data->path);
		free(data);
	}
}
