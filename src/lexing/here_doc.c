/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:46:58 by wailas            #+#    #+#             */
/*   Updated: 2025/05/14 15:07:02 by wailas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*here_doc(t_data *data, char *delimiter)
{
	char	*here_doc;
	char	*line;
	char	*tmp;

	here_doc = NULL;
	if (data->tokens->type == CMD || data->tokens->type == ARG)
	{
		while (true)
		{
			ft_printf("Here_doc > ");
			line = get_next_line(0, 0);
			if (!line)
				break ;
			line[len(line) - 1] = '\0';
			if (ft_strcmp(line, delimiter) == 0)
			{
				free(line);
				break ;
			}
			if (!here_doc)
				here_doc = ft_strdup(line);
			else
			{
				tmp = ft_strjoin(here_doc, line);
				free(here_doc);
				here_doc = tmp;
			}
			free(line);
		}
	}
	return (here_doc);
}
