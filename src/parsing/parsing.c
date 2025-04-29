/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 18:47:32 by wailas            #+#    #+#             */
/*   Updated: 2025/04/29 15:07:18 by wailas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	parse_command(t_data data, char *input)
{
	char	*line;

	if (!valid_quotes(input))
		return ;
	line = expend_vars(data, input);
	token(line);
	if (!*line)
		return ;
	//ft_printf("%s\n", line);
}
