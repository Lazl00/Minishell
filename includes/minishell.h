/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 16:49:35 by lcournoy          #+#    #+#             */
/*   Updated: 2025/06/11 12:04:24 by wailas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <ctype.h>
# include <dlfcn.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/include/libft.h"
# include "../libft/include/ft_printf.h"
# include "../libft/include/get_next_line.h"

extern pid_t	g_signal_pid;

typedef enum s_token_parse {
	CMD,
	CMD_BUILTIN,
	REDIR_IN,
	REDIR_OUT,
	PIPE,
	OUTFILE,
	INFILE,
	DELIMITEUR,
	DELIMITEUR_MOT,
	APPEND,
	APPEND_FILE,
	ARG,
}	t_enum_token;

typedef struct s_token {
	char			*value;
	t_enum_token	type;
	struct s_token	*next;
	int				heredoc_fd;
	bool			ignore;
}	t_token;

typedef struct s_data {
	char	**env;
	t_token	*tokens;
	int		fd[2];
	int		exit_status;
}	t_data;

typedef enum e_signal_mode {
	PARENT,
	CHILD
}	t_signal_mode;

typedef struct s_exec_context
{
	t_token	*cmd;
	t_token	*segment_start;
	t_token	*segment_end;
	int		prev_pipe[2];
	int		pipe_fd[2];
	pid_t	last_pid;
}	t_exec_context;

// void
void	free_tokens(t_token *token);
void	print_token_list(t_token *head);
void	token_remove_quote(t_token *list);
void	access_token_cmd(t_token *list);
void	free_data(t_data *data);
void	free_data_main(t_data *data);
void	free_tab(char **str);
void	minishell_loop(t_data *data);
void	print_str_array(char **arr);
void	ft_child_infile(t_data *data, int fd_gen[2]);
void	ft_parent_outfile(t_data *data, int fd_gen[2]);
void	ft_child_cmd(t_token *token, char **env,
			int prev_pipe[2], int next_pipe[2]);
void	ft_parent_cmd(int prev_pipe[2]);
void	ft_exec(t_data *data);
void	handle_redirections(t_token *cmd);
void	save_and_redirect_stdout(int fd, int *saved);
void	restore_stdout(int saved);
void	ft_replace_env(t_data *data, char *var, char *value);
void	ft_error(const char *msg, const char *detail);
void	configure_signals(t_signal_mode mode);
void	exit_clean(t_data *data, char **argv, int status);
void	exit_perror(char *msg);
void	prepare_heredocs(t_data *data, t_token *tokens);
void	move_command_to_front(t_token *segment_start);
void	exec_loop(t_data *data);
void	init_pipes(int *pipe_fd, int *has_pipe, t_token *segment_end);
void	update_prev_pipe(int prev_pipe[2], int pipe_fd[2]);
void	exec_child(t_data *data, t_token *start,
			int prev_pipe[2], int pipe_fd[2]);
void	exec_dispatch(t_data *data, t_token *start);
void	exec_external(t_data *data, t_token *start);
void	exit_execve_errno(void);
void	setup_pipes_and_redirects(t_token *cmd, int prev[2], int fds[2]);
void	move_outfiles(t_token *segment_start);
void	move_outfiles_to_last(t_token *segment_start);
void	token_swap(t_token *first, t_token *second);
void	append_token(t_token **head, t_token *to_add);
void	add_all_matching_tokens(t_token **phoenix,
			t_token **deprecated, t_token *(*finder)(t_token **));
void	extract_redir_out_pairs(t_token **phoenix, t_token **deprecated);
void	extract_redir_in_pairs(t_token **phoenix, t_token **deprecated);
void	extract_heredoc_pairs(t_token **phoenix, t_token **deprecated);
void	extract_args_after_cmd(t_token **phoenix, t_token **deprecated);
void	process_type(t_token **phoenix, t_token *segment);
void	append_pipe_if_needed(t_token **phoenix, t_token *pipe);
void	sigint_handler(int sig);

// bool
bool	add_token_to_list(t_token **head, t_token **last, t_token *token);
bool	valid_quotes(char *line);
bool	check_quote_state(char *line, int pos, char c);
bool	in_any_quote(char *line, int pos);
bool	is_separator(char c);
bool	is_quoted(char *str);
bool	is_builtin(t_token *token);
bool	ft_echo(t_data *data, t_token *token);
bool	ft_cd(t_data *data, t_token *token);
bool	ft_pwd(t_data *data, t_token *token);
bool	ft_export(t_data *data, t_token *token);
bool	ft_unset(t_data *data, t_token *token);
bool	check_pipe(t_token *token);
bool	lexing(t_data *data);
bool	ft_exit(t_data *data, t_token *token);
bool	check_outfile(t_token *tokens);
bool	check_infile(t_token *token);
bool	check(t_token *token);
bool	check_delimiter(t_token *token);
bool	check_append(t_token *tokens);
bool	check_cmd(t_token *token);
bool	check_open(t_token *tokens);
bool	check_file(t_token *token, int *fd);
bool	check_access(t_data *data);
bool	update_pwd_env(t_data *data, char *oldpwd);
bool	new_token(t_token **head, t_token *new_token);
bool	move_token_pair(t_token **phoenix, t_token **deprecated,
			t_token **cur, t_token **prev);
bool	is_heredoc(char	*line, int i);
bool	has_pipe(t_token *tokens);

// int
int		quote_counter(char *line);
int		ft_env(t_data *data, t_token *token);
int		pipe_number(t_data *data);
int		find_outfile_fd(t_token *cmd);
int		get_pipe(t_data *data);
int		do_builtin(t_data *data, t_token *token);
int		print_error(char *str);
int		copy_clean_var(char *dst, char *src, int i);
int		count_outfiles(t_token *segment_start);
int		interpret_status(int status);
int		do_heredoc(t_data *data, char *delimiter);

// char *
char	*quotes_remover(char *line);
char	*expend_vars(t_data data, char *line);
char	*modified_var(t_data data, char *var);
char	*cut_var(char *var);
char	*input_with_space(char *str);
char	*check_exec(t_data *data, t_token *token, char **env);
char	*get_cmd_path(char *cmd, char **envp);
char	*simple_expend(t_data data, char *line, char *var, int i);

// char **
char	**build_argv(t_token *cmd);

// t_token *
t_token	*create_token(t_enum_token type, char *value);
t_token	*create_token_from_value(char *token_value);
t_token	*token(char *input);
t_token	*find_first_cmd(t_token *segment_start);
t_token	*find_command_token(t_token *start);
t_token	*find_cmd(t_token *segment_start);
t_token	*get_segment_end(t_token *start);
t_token	*find_last_heredoc(t_token *cmd);
t_token	*find_next_token_of_type(t_token **deprecated, t_enum_token type);
t_token	*find_cmd_phoenix(t_token **deprecated);
t_token	*phoenix(t_token **deprecated);
t_token	*find_append_signe_phoenix(t_token **deprecated);
t_token	*find_delimiteur_phoenix(t_token **deprecated);
t_token	*find_append_file_phoenix(t_token **deprecated);
t_token	*find_delimiteur_mot_phoenix(t_token **deprecated);
t_token	*split_segment_at_pipe(t_token **segment, t_token **rest);

// t_data *
t_data	*parse_command(t_data *data, char *input);
t_data	*init_data(t_data *data, char **env);

// pid_t
pid_t	process_segment(t_data *data, t_token *start, int prev[2], int pipe[2]);

#endif
