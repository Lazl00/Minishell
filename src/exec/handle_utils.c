/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 15:02:46 by wailas            #+#    #+#             */
/*   Updated: 2025/05/30 15:02:59 by wailas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*find_last_heredoc(t_token *cmd)
{
	t_token	*last;

	last = NULL;
	while (cmd && cmd->type != PIPE)
	{
		if (cmd->type == DELIMITEUR && cmd->heredoc_fd != -1)
			last = cmd;
		cmd = cmd->next;
	}
	return (last);
}
