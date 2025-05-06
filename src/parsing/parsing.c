/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcournoy <lcournoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 18:47:32 by wailas            #+#    #+#             */
/*   Updated: 2025/05/06 15:48:48 by lcournoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token_node	*parse_command(t_data data, char *input)
{
	char			*line;
	t_token_node	*tokens;

	if (!valid_quotes(input))
		return (NULL);
	line = expend_vars(data, input);
	tokens = token(line);
	return (tokens);
}
