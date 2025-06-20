/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:54:50 by lcournoy          #+#    #+#             */
/*   Updated: 2025/06/20 11:02:48 by wailas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exit_fd(void *fill)
{
	int fd;

	(void)fill;
	fd = 3;
	while (fd < 1024)
	{
		close(fd);
		fd++;
	}
}

void    close_all_except(int keep1, int keep2)
{
    static int    fd = 3;

    if (fd >= 1024)
    {
        fd = 3;
        return ;
    }
    if (fd != keep1 && fd != keep2)
        close(fd);
    fd++;
    close_all_except(keep1, keep2);
}

int	prepare_heredocs(t_data *data, t_token *tokens)
{
	t_token	*tmp;
	int fd;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == 7 && tmp->next && tmp->next->type == 8)
		{
			fd = do_heredoc(data, tmp->next->value, NULL);
			if (fd < 0)
			{
				close_all_heredocs(data->tokens);
				return (-1);
			}
			tmp->heredoc_fd = fd;
		}
		tmp = tmp->next;
	}
	return (1);
}

void	sigint_handler_heredoc(int sig)
{
	(void)sig;
	exit_pipe(-1);
	exit_str(NULL, 0);
	exit_buffer(NULL);
	buf_manager(NULL);
	exit_hdoc(NULL);
	exit_fd(NULL);
	exit(42);
}

int	do_heredoc(t_data *data, char *delimiter, char *line)
{
	int		pipe_fd[2];
	pid_t	pid;
	int		status;
	struct sigaction sa_old, sa_new;
	char *trimmed;

	if (pipe(pipe_fd) == -1)
		return (-1);
	sa_new.sa_handler = SIG_IGN;
	sigemptyset(&sa_new.sa_mask);
	sa_new.sa_flags = 0;
	sigaction(SIGINT, &sa_new, &sa_old);

	pid = fork();
	if (pid < 0)
		return (-1);
	else if (pid == 0) 
	{
		exit_hdoc(data);
		exit_pipe(pipe_fd[1]);
		signal(SIGINT, sigint_handler_heredoc);
		signal(SIGQUIT, SIG_IGN);
		close(pipe_fd[0]);
		while (1)
		{
			write(1, "> ", 2);
			line = get_next_line(0, 0);
			if (!line)
			{
				write(2, "\n", 2);
				exit_str(NULL, 0);
				break ;
			}
			trimmed = ft_strtrim(line, "\n");
			if (ft_strcmp(trimmed, delimiter) == 0)
			{
				free(trimmed);
				break ;
			}
			char *expanded = expend_vars(*data, trimmed, 0, 0);
			write(pipe_fd[1], expanded, len(expanded));
			write(pipe_fd[1], "\n", 1);
			free(expanded);
			exit_str(NULL, 1);
		}
		buf_manager(NULL);
		free_data(data);
		close(pipe_fd[1]);
		close_all_except(pipe_fd[1], 1);
		exit(0);
	}
	else
	{
		close(pipe_fd[1]);
		waitpid(pid, &status, 0);
		sigaction(SIGINT, &sa_old, NULL);
		configure_signals(PARENT);

		if (WIFEXITED(status))
		{
			int code = WEXITSTATUS(status);
			if (code == 42)
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
}

t_token	*find_last_heredoc(t_token *cmd)
{
	t_token	*last;

	last = NULL;
	while (cmd && cmd->type != PIPE)
	{
		if (cmd->type == DELIMITEUR && cmd->heredoc_fd != -1)
			last = cmd;
		cmd = cmd->next;
	}
	return (last);
}

void	close_all_heredocs(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->heredoc_fd != -1)
		{
			close(tmp->heredoc_fd);
			tmp->heredoc_fd = -1;
		}
		tmp = tmp->next;
	}
}
