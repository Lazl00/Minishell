/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcournoy <lcournoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 18:47:32 by wailas            #+#    #+#             */
/*   Updated: 2025/04/16 13:36:51 by lcournoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	parse_command(t_data data, char *input)
{
	if (!valid_quotes(input))
		return ;
	if (!expend_vars(data, input))
		return ;
}

// && !create_token_list(input)