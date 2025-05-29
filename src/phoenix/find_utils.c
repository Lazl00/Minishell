/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:17:49 by lcournoy          #+#    #+#             */
/*   Updated: 2025/05/29 05:40:44 by wailas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token *find_outfile_signe_phoenix(t_token **deprecated)
{
    return find_next_token_of_type(deprecated, REDIR_OUT);
}

t_token *find_append_signe_phoenix(t_token **deprecated)
{
    return find_next_token_of_type(deprecated, APPEND);
}

t_token *find_append_file_phoenix(t_token **deprecated)
{
    return find_next_token_of_type(deprecated, APPEND_FILE);
}

t_token *find_delimiteur_phoenix(t_token **deprecated)
{
    return find_next_token_of_type(deprecated, DELIMITEUR);
}

t_token *find_delimiteur_mot_phoenix(t_token **deprecated)
{
    return find_next_token_of_type(deprecated, DELIMITEUR_MOT);
}
