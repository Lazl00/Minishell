/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 18:48:25 by wailas            #+#    #+#             */
/*   Updated: 2025/05/27 13:22:32 by wailas           ###   ########.fr       */
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
