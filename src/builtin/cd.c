/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:27:14 by lcournoy          #+#    #+#             */
/*   Updated: 2025/05/19 16:39:30 by wailas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_cd(t_data *data, t_token *token)
{
    // char	*oldpwd;
    // char	*pwd;

    (void)data;
    //printf("%s\n", getcwd(NULL, 0));
    if (token->next->type == ARG || ft_strncmp (token->next->value, "..", 2) == 0)
    {
        chdir(token->next->value);
    }
	return (true);
}

// char    *get_full_path()
