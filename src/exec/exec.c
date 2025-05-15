/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:25:16 by wailas            #+#    #+#             */
/*   Updated: 2025/05/15 18:06:38 by wailas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    ft_exec(t_data *data)
{
    t_token *tmp = data->tokens;
    int prev_pipe[2] = {-1, -1};
    int next_pipe[2];
    pid_t pid;

    while (tmp)
    {
        if (tmp->next && tmp->next->type == PIPE)
            pipe(next_pipe);
        else
            next_pipe[0] = next_pipe[1] = -1;

        pid = fork();
        if (pid == 0)
        {
            if (tmp->prev && tmp->prev->type == INFILE)
                ft_child_infile(data, next_pipe);
            else if (tmp->next && tmp->next->type == OUTFILE)
                ft_parent_outfile(data, prev_pipe);
            else
                ft_child_cmd(tmp, data->env, prev_pipe, next_pipe);
        }
        else
        {
            ft_parent_cmd(prev_pipe);
        }
        prev_pipe[0] = next_pipe[0];
        prev_pipe[1] = next_pipe[1];
        tmp = tmp->next;
    }
}

int    pipe_number(t_data *data)
{
    t_token    *tmp;
    int        count;

    tmp = data->tokens;
    count = 0;
    while (tmp)
    {
        if (tmp->type == CMD)
            count++;
        tmp = tmp->next;
    }
    return (count);
}

void    ft_child_infile(t_data *data, int fd_gen[2])
{
    int    fd;
    t_token    *tmp;

    tmp = data->tokens;
    char    *cmd[] = {tmp->value, NULL};
    fd = open(tmp->value, O_RDWR);
    if (fd == -1)
    {
        perror("Error\n");
        exit(1);
    }
    dup2(fd, STDIN_FILENO);
    dup2(fd_gen[1], STDOUT_FILENO);
    close(fd_gen[1]);
    close(fd_gen[0]);
    close(fd);
    execve(tmp->value, cmd , data->env);
}

void    ft_parent_outfile(t_data *data, int fd_gen[2])
{
    int    fd;
    t_token    *tmp;

    tmp = data->tokens;
    fd = open(tmp->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1)
    {
        perror("Error\n");
        exit(1);
    }
    char    *cmd[] = {tmp->value, NULL};
    dup2(fd, STDOUT_FILENO);
    dup2(fd_gen[0], STDIN_FILENO);
    close(fd_gen[0]);
    close(fd_gen[1]);
    close(fd);
    execve(tmp->value, cmd, data->env);
}

void ft_child_cmd(t_token *token, char **env, int prev_pipe[2], int next_pipe[2])
{
    if (prev_pipe[0] != -1)
    {
        dup2(prev_pipe[0], STDIN_FILENO);
        close(prev_pipe[0]);
        close(prev_pipe[1]);
    }
    if (next_pipe[1] != -1)
    {
        dup2(next_pipe[1], STDOUT_FILENO);
        close(next_pipe[0]);
        close(next_pipe[1]);
    }
    char *cmd[] = {token->value, NULL};
    execve(cmd[0], cmd, env);
    perror("execve");
    exit(EXIT_FAILURE);
}


void ft_parent_cmd(int prev_pipe[2])
{
    if (prev_pipe[0] != -1)
    {
        close(prev_pipe[0]);
        close(prev_pipe[1]);
    }
}
