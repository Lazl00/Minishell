/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_heredocs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcournoy <lcournoy@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-20 10:16:14 by lcournoy          #+#    #+#             */
/*   Updated: 2025/06/20 12:25:14 by lcournoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	hdoc_child(t_data *data, char *delimiter, int write_fd)
{
	t_hd	hd;

	norminette_hd(data, write_fd);
	while (1)
	{
		write(1, "> ", 2);
		hd.line = get_next_line(0, 0);
		if (!hd.line)
		{
			norminette_hd2();
			break ;
		}
		hd.trim = ft_strtrim(hd.line, "\n");
		if (ft_strcmp(hd.trim, delimiter) == 0)
		{
			free(hd.trim);
			break ;
		}
		hd.exp = expend_vars(*data, hd.trim, 0, 0);
		write(write_fd, hd.exp, len(hd.exp));
		write(write_fd, "\n", 1);
		free(hd.exp);
		exit_str(NULL, 1);
	}
	return (0);
}

int	hdoc_fork(t_data *data, char *delimiter, int *pipe_fd)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (-1);
	else if (pid == 0)
	{
		close(pipe_fd[0]);
		hdoc_child(data, delimiter, pipe_fd[1]);
		buf_manager(NULL);
		free_data(data);
		close(pipe_fd[1]);
		close_all_except(pipe_fd[1], 1);
		exit(0);
	}
	return (pid);
}

int	hdoc_wait(pid_t pid, int *pipe_fd)
{
	int	status;

	close(pipe_fd[1]);
	waitpid(pid, &status, 0);
	configure_signals(PARENT);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 42)
	{
		write(1, "\n", 1);
		close(pipe_fd[0]);
		g_signal_pid = 42;
		return (-1);
	}
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		write(1, "\n", 1);
		close(pipe_fd[0]);
		g_signal_pid = 42;
		return (-1);
	}
	return (pipe_fd[0]);
}

int	do_heredoc(t_data *data, char *delimiter)
{
	int		pipe_fd[2];
	pid_t	pid;
	void	(*prev_handler)(int);

	if (pipe(pipe_fd) == -1)
		return (-1);
	prev_handler = signal(SIGINT, SIG_IGN);
	pid = hdoc_fork(data, delimiter, pipe_fd);
	if (pid < 0)
		return (-1);
	signal(SIGINT, prev_handler);
	return (hdoc_wait(pid, pipe_fd));
}
