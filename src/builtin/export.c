/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcournoy <lcournoy@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-15 14:27:42 by lcournoy          #+#    #+#             */
/*   Updated: 2025-05-15 14:27:42 by lcournoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool    ft_export(t_data *data, t_token *token)
{
    int		i;
    char	**new_env;

    if (!data || !data->env)
        return (false);
    i = 0;
    while (data->env[i])
        i++;
    new_env = malloc(sizeof(char *) * (i + 2));
    if (!new_env)
        return (false);
    i = 0;
    while (data->env[i])
    {
        new_env[i] = data->env[i];
        i++;
    }
    new_env[i] = ft_strdup(token->next->value);
    new_env[i + 1] = NULL;
    free(data->env);
    data->env = new_env;
    return (true);
}