/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:46:58 by wailas            #+#    #+#             */
/*   Updated: 2025/05/13 15:27:31 by wailas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*here_doc(t_data *data, char *delimiter)
{
	char	*here_doc;
	char	*line;
	char	*tmp;

	if (data->tokens->type != CMD)
		return (NULL);
	ft_printf("Here_doc > ");
	while (true)
	{
		line = get_next_line(0, 0);
		if (!line)
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
		if (ft_strcmp(here_doc, delimiter))
			break ;
	}
	return (here_doc);
}
