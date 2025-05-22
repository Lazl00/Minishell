/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcournoy <lcournoy@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-22 14:54:50 by lcournoy          #+#    #+#             */
/*   Updated: 2025-05-22 14:54:50 by lcournoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void prepare_heredocs(t_token *tokens)
{
    t_token *tmp = tokens;

    while (tmp)
    {
        if (tmp->type == DELIMITEUR && tmp->next && tmp->next->type == DELIMITEUR_MOT)
        {
            int fd = handle_heredoc(tmp->next->value);
            if (fd < 0)
            {
                perror("heredoc");
                exit(1);
            }
            tmp->heredoc_fd = fd;
        }
        tmp = tmp->next;
    }
}
int handle_heredoc(const char *delimiter)
{
    int pipe_fd[2];
    char *line;

    if (pipe(pipe_fd) == -1)
    {
        perror("pipe");
        return -1;
    }

    while (1)
    {
        line = readline("> ");
        if (!line || strcmp(line, delimiter) == 0)
        {
            free(line);
            break;
        }
        write(pipe_fd[1], line, strlen(line));
        write(pipe_fd[1], "\n", 1);
        free(line);
    }

    close(pipe_fd[1]); // ferme l'écriture
    return pipe_fd[0]; // retourne le descripteur de lecture
}
