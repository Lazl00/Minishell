/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 18:47:32 by wailas            #+#    #+#             */
/*   Updated: 2025/05/07 14:42:45 by wailas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_data	*parse_command(t_data *data, char *input)
{
	char	*line;

	if (!valid_quotes(input))
		return (NULL);
	line = expend_vars(*data, input);
	(*data).tokens = token(line);
	return (data);
}
