/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 05:36:10 by wailas            #+#    #+#             */
/*   Updated: 2025/06/02 18:06:02 by wailas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*find_pipe_phoenix(t_token **deprecated)
{
	return (find_next_token_of_type(deprecated, PIPE));
}

t_token	*find_arg_phoenix(t_token **deprecated)
{
	return (find_next_token_of_type(deprecated, ARG));
}

t_token	*find_infile_signe_phoenix(t_token **deprecated)
{
	return (find_next_token_of_type(deprecated, REDIR_IN));
}

t_token	*find_infile_phoenix(t_token **deprecated)
{
	return (find_next_token_of_type(deprecated, INFILE));
}
