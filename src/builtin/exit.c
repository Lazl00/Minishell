/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcournoy <lcournoy@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-15 14:28:04 by lcournoy          #+#    #+#             */
/*   Updated: 2025/05/22 15:01:32 by lcournoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_exit(t_data *data, t_token *token)
{
	t_token	*tmp;

	tmp = token;
	if (!data || !data->tokens)
		return (false);
	if (tmp->next && tmp->next->type == ARG)
	{
		if (tmp->next->next && tmp->next->next->type == ARG)
			return (print_error("exit: too many arguments"));
	}
	free_data(data);
	exit(0);
}
