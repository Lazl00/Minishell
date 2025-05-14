/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 18:17:42 by wailas            #+#    #+#             */
/*   Updated: 2025/05/14 18:18:52 by wailas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool env(t_data *data)
{
    int	i;

    i = 0;
    if (!data || !data->env)
        return (false);
    while (data->env[i])
    {
        printf("%s\n", data->env[i]);
        i++;
    }
    return (true);
}