/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:25:16 by wailas            #+#    #+#             */
/*   Updated: 2025/05/20 17:31:54 by wailas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void handle_redirections(t_token *cmd)
{
    int fd;

    while (cmd && cmd->type != PIPE)
    {
        if (cmd->type == REDIR_IN && cmd->next)
        {
            fd = open(cmd->next->value, O_RDONLY);
            if (fd < 0)
            {
                perror("infile");
                exit(1);
            }
            dup2(fd, STDIN_FILENO);
            close(fd);
        }
        else if (cmd->type == REDIR_OUT && cmd->next)
        {
            fd = open(cmd->next->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd < 0)
            {
                perror("outfile");
                exit(1);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        else if (cmd->type == APPEND && cmd->next)
        {
            fd = open(cmd->next->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd < 0)
            {
                perror("append");
                exit(1);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        cmd = cmd->next;
    }
}

char **build_argv(t_token *cmd)
{
    int size = 0;
    t_token *tmp;
    int i = 0;
    char **argv;

    tmp = cmd;
    while (tmp && tmp->type != PIPE)
    {
        if (tmp->type == CMD || tmp->type == ARG)
            size++;
        tmp = tmp->next;
    }
    argv = malloc(sizeof(char *) * (size + 1));
    if (!argv)
        return NULL;
    tmp = cmd;
    i = 0;
    while (tmp && tmp->type != PIPE)
    {
        if (tmp->type == CMD || tmp->type == ARG)
        {
            argv[i] = tmp->value;
            i++;
        }
        tmp = tmp->next;
    }
    argv[i] = NULL;
    return argv;
}

void exec_loop(t_data *data)
{
	t_token *cmd = data->tokens;
	t_token *segment_start;
	t_token *segment_end;
	int     prev_pipe[2] = {-1, -1};
	int     pipe_fd[2];
	pid_t   pid;
	int     has_pipe;

	while (cmd)
	{
		segment_start = cmd;
		segment_end = get_segment_end(segment_start);
		init_pipes(pipe_fd, &has_pipe, segment_end);
		pid = fork();
		if (pid == 0)
			child_process(segment_start, prev_pipe, pipe_fd, data);
		else if (pid < 0)
		{
			perror("fork");
			exit(1);
		}
		update_pipe_and_cmd(prev_pipe, segment_end, &cmd, pipe_fd);
	}
}

void	update_pipe_and_cmd(int prev_pipe[2], t_token *segment_end, t_token **cmd, int pipe_fd[2])
{
	if (prev_pipe[0] != -1)
	{
		close(prev_pipe[0]);
		close(prev_pipe[1]);
	}
	prev_pipe[0] = pipe_fd[0];
	prev_pipe[1] = pipe_fd[1];
	if (segment_end)
		*cmd = segment_end->next;
	else
		*cmd = NULL;
}

void ft_exec(t_data *data)
{
	exec_loop(data);
	while (wait(NULL) > 0)
		;
}
