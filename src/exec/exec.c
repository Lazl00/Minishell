/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:25:16 by wailas            #+#    #+#             */
/*   Updated: 2025/05/22 15:08:02 by lcournoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**build_argv(t_token *cmd)
{
	int		size;
	t_token	*tmp;
	int		i;
	char	**argv;

	i = 0;
	size = 0;
	tmp = cmd;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == CMD || tmp->type == ARG)
			size++;
		tmp = tmp->next;
	}
	argv = malloc(sizeof(char *) * (size + 1));
	if (!argv)
		return (NULL);
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
	return (argv);
}

void	exec_loop(t_data *data)
{
	t_token	*cmd = data->tokens;
	t_token	*segment_start;
	t_token	*segment_end;
	int		prev_pipe[2] = {-1, -1};
	int		pipe_fd[2];
	pid_t	pid;

	while (cmd)
	{
		segment_start = cmd;
		segment_end = get_segment_end(segment_start);
		int has_pipe = segment_end && segment_end->next && segment_end->next->type == PIPE;
		init_pipes(pipe_fd, &has_pipe, segment_end);
		if (is_builtin(segment_start) && !has_pipe && prev_pipe[0] == -1)
			data->exit_status = do_builtin(data, segment_start);
		else
		{
			pid = fork();
			if (pid == 0)
			{
				if (prev_pipe[0] != -1)
				{
					dup2(prev_pipe[0], STDIN_FILENO);
					close(prev_pipe[0]);
					close(prev_pipe[1]);
				}
				if (pipe_fd[1] != -1)
				{
					dup2(pipe_fd[1], STDOUT_FILENO);
					close(pipe_fd[0]);
					close(pipe_fd[1]);
				}
				handle_redirections(segment_start);
				if (is_builtin(segment_start))
                {
                    int culled = do_builtin(data, segment_start);
                    free_data(data);
					exit(culled);
                }
				else
                {
                	if (!segment_start || !segment_start->value)
                    {
                    	free_data(data);
                    	exit(127);
                    }
                	char **argv = build_argv(segment_start);
                	if (!argv)
                    {
                    	free_data(data);
                    	exit(1);
                    }
                	execve(segment_start->value, argv, data->env);
                	perror("execve");
					free_data(data);
					free(argv);
					if (errno == EACCES)
					    exit(126);
					else if (errno == ENOENT)
					    exit(127);
					else
					    exit(1);
                }
			}
			else if (pid < 0)
			{
				perror("fork");
				exit(1);
			}
		}
		if (prev_pipe[0] != -1)
		{
			close(prev_pipe[0]);
			close(prev_pipe[1]);
		}
		prev_pipe[0] = pipe_fd[0];
		prev_pipe[1] = pipe_fd[1];
        if (segment_end)
            cmd = segment_end->next;
        else
            cmd = NULL;
	}
}

void	move_command_to_front(t_token *segment_start)
{
	t_token *cur = segment_start;
	t_token *first_cmd = NULL;
	t_token *before_cmd = NULL;

	while (cur && cur->type != PIPE)
	{
		if (cur->type == CMD || cur->type == CMD_BUILTIN || cur->type == ARG)
		{
			first_cmd = cur;
			break;
		}
		before_cmd = cur;
		cur = cur->next;
	}
	if (!first_cmd || first_cmd == segment_start)
		return;
	int saved_type = first_cmd->type;
	char *saved_value = first_cmd->value;
	t_token *tmp = first_cmd;
	while (tmp != segment_start)
	{
		t_token *prev = segment_start;
		while (prev->next != tmp)
			prev = prev->next;

		tmp->type = prev->type;
		tmp->value = prev->value;
		tmp = prev;
	}
	segment_start->type = saved_type;
	segment_start->value = saved_value;
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

void	ft_exec(t_data *data)
{
	prepare_heredocs(data->tokens);
	exec_loop(data);

	int	status;
	pid_t pid;
	while ((pid = wait(&status)) > 0)
	{
		if (WIFEXITED(status))
			data->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			data->exit_status = 128 + WTERMSIG(status);
	}
}