/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcournoy <lcournoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 14:47:00 by lcournoy          #+#    #+#             */
/*   Updated: 2025/04/28 12:38:27 by wailas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_echo(t_data *data, t_token *token)
{
    int		i;
    int		fd;
    bool	new_line;

    if (!data || !data->tokens)
        return (false);
    i = 0;
    new_line = true;
    if (token->next && ft_strncmp(token->next->value, ">", 1) == 0)
    {
        fd = find_outfile_fd(token);
        if (fd < 0)
            return (false);
    }
    else
        fd = STDOUT_FILENO;
    while (token->next && token->next->type != PIPE)
    {
        if (ft_strncmp(token->next->value, "-n", 2) == 0)
            new_line = false;
        else
            ft_putstr_fd(token->next->value, fd);
        token = token->next;
        if (token && token->type != PIPE)
            ft_putchar_fd(' ', fd);
    }
    if (new_line)
        ft_putchar_fd('\n', fd);
    if (fd != STDOUT_FILENO)
        close(fd);
    return (true);
}