/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   true_phoenix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 18:18:17 by wailas            #+#    #+#             */
/*   Updated: 2025/06/02 18:28:12 by wailas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*phoenix(t_token **deprecated)
{
	t_token	*phoenix;
	t_token	*segment;
	t_token	*pipe;

	phoenix = NULL;
	while (*deprecated)
	{
		segment = *deprecated;
		pipe = split_segment_at_pipe(&segment, deprecated);
		process_type(&phoenix, segment);
		append_pipe_if_needed(&phoenix, pipe);
	}
	return (phoenix);
}

t_token	*split_segment_at_pipe(t_token **segment, t_token **rest)
{
	t_token	*cur;
	t_token	*prev;

	cur = *segment;
	prev = NULL;
	while (cur && cur->type != PIPE)
	{
		prev = cur;
		cur = cur->next;
	}
	if (cur && cur->type == PIPE)
	{
		*rest = cur->next;
		cur->next = NULL;
		return (cur);
	}
	*rest = NULL;
	return (NULL);
}

void	process_type(t_token **phoenix, t_token *segment)
{
	t_token	*to_add;

	to_add = find_cmd_phoenix(&segment);
	if (to_add)
		append_token(phoenix, to_add);
	extract_args_after_cmd(phoenix, &segment);
	extract_redir_in_pairs(phoenix, &segment);
	extract_heredoc_pairs(phoenix, &segment);
	extract_redir_out_pairs(phoenix, &segment);
	add_all_matching_tokens(phoenix, &segment, find_append_signe_phoenix);
	add_all_matching_tokens(phoenix, &segment, find_append_file_phoenix);
	add_all_matching_tokens(phoenix, &segment, find_delimiteur_phoenix);
	add_all_matching_tokens(phoenix, &segment, find_delimiteur_mot_phoenix);
}

void	append_pipe_if_needed(t_token **phoenix, t_token *pipe)
{
	if (pipe)
		append_token(phoenix, pipe);
}
