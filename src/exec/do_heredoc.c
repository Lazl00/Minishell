/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcournoy <lcournoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 01:09:48 by lcournoy          #+#    #+#             */
/*   Updated: 2025/06/20 01:09:48 by lcournoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	do_heredoc(t_data *data, char *delimiter, char *line)
{
	int					pipe_fd[2];
	pid_t				pid;
	struct sigaction	sa_new;

	(void)line;
	if (pipe(pipe_fd) == -1)
		return (-1);
	sa_new.sa_handler = SIG_IGN;
	sigemptyset(&sa_new.sa_mask);
	sa_new.sa_flags = 0;
	sigaction(SIGINT, &sa_new, NULL);
	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
		heredoc_child(data, delimiter, pipe_fd);
	return (heredoc_parent(pipe_fd, pid));
}
void	heredoc_child(t_data *data, char *delimiter, int pipe_fd[2])
{
	char	*line;
	char	*trimmed;
	char	*expanded;

	signal(SIGINT, sigint_handler_heredoc);
	signal(SIGQUIT, SIG_IGN);
	close(pipe_fd[0]);
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0, 0);
		if (!line)
			break ;
		trimmed = ft_strtrim(line, "\n");
		if (!trimmed || ft_strcmp(trimmed, delimiter) == 0)
			break ;
		expanded = expend_vars(*data, trimmed, 0, 0);
		write(pipe_fd[1], expanded, len(expanded));
		write(pipe_fd[1], "\n", 1);
		free(trimmed);
		free(expanded);
	}
	heredoc_child_exit(data, pipe_fd[1], trimmed);
}
void	heredoc_child_exit(t_data *data, int write_end, char *trimmed)
{
	free(trimmed);
	buf_manager(NULL);
	free_data(data);
	close(write_end);
    close_all_except(write_end, 1);
	exit(0);
}
int	heredoc_parent(int pipe_fd[2], pid_t pid)
{
	int		status;

	close(pipe_fd[1]);
	waitpid(pid, &status, 0);
	sigaction(SIGINT, NULL, NULL);
	configure_signals(PARENT);
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == 42)
		{
			write(1, "\n", 1);
			close(pipe_fd[0]);
			g_signal_pid = 42;
			return (-1);
		}
	}
	else if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		write(1, "\n", 1);
		close(pipe_fd[0]);
		g_signal_pid = 42;
		return (-1);
	}
	return (pipe_fd[0]);
}
