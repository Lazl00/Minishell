/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 18:48:25 by wailas            #+#    #+#             */
/*   Updated: 2025/05/07 17:01:53 by wailas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_token(t_token *token)
{
	if (token)
	{
		free(token->value);
		free(token);
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
		while (data->tokens)
		{
			t_token *temp = data->tokens->next;
			free_token(data->tokens);
			data->tokens = temp;
		}
		//free(data->path);
		free(data);
	}
}