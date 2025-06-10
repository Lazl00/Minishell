/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:46:58 by wailas            #+#    #+#             */
/*   Updated: 2025/05/27 13:30:00 by wailas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	rassemble(char *here_doc, char *line, char *tmp)
{
	if (!here_doc)
		here_doc = ft_strdup(line);
	else
	{
		tmp = ft_strjoin(here_doc, line);
		free(here_doc);
		here_doc = tmp;
	}
}
