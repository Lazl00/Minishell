/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 16:49:35 by lcournoy          #+#    #+#             */
/*   Updated: 2025/05/27 14:38:23 by wailas           ###   ########.fr       */
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

/* ===========================
	Token Management Functions
	=========================== */
t_token	*create_token(t_enum_token type, char *value);
void	free_tokens(t_token *token);
t_token	*create_token_from_value(char *token_value);

/* ===========================
	Token List Functions
	=========================== */
bool	add_token_to_list(t_token **head, t_token **last, t_token *token);
void	print_token_list(t_token *head);
void	token_remove_quote(t_token *list);
void	access_token_cmd(t_token *list);

/* ===========================
	Parsing Functions
	=========================== */
t_data	*parse_command(t_data *data, char *input);
t_token	*token(char *input);
void	add_token(char *token_value, t_enum_token type);

/* ===========================
	Quote Handling Functions
	=========================== */
bool	valid_quotes(char *line);
bool	check_quote_state(char *line, int pos, char c);
bool	in_any_quote(char *line, int pos);
int		quote_counter(char *line);
char	*quotes_remover(char *line);

/* ===========================
	Variable Expansion Functions
	=========================== */
char	*expend_vars(t_data data, char *line);
char	*modified_var(t_data data, char *var);
char	*cut_var(char *var);

/* ===========================
	Utility Functions
	=========================== */
bool	is_separator(char c);
bool	is_quoted(char *str);
bool	is_builtin(t_token *token);

/* ===========================
	Input Handling Functions
	=========================== */
char	*input_with_space(char *str);
void	add_operator_with_spaces(char *new_input, char *input, int *i, int *j);

/* ===========================
	Built-in Commands
	=========================== */
bool	ft_echo(t_data *data, t_token *token);
bool	ft_cd(t_data *data, t_token *token);
bool	ft_pwd(t_data *data, t_token *token);
bool	ft_export(t_data *data, t_token *token);
bool	ft_unset(t_data *data, t_token *token);
bool	ft_env(t_data *data, t_token *token);
bool	ft_exit(t_data *data, t_token *token);

/* ===========================
	Data Management
	=========================== */
t_data	*init_data(t_data *data, char **env);
void	free_data(t_data *data);
void	free_data_main(t_data *data);

/* ===========================
	Token Checking & Lexing
	=========================== */
bool	check_pipe(t_token *token);
bool	lexing(t_data *data);
bool	check_outfile(t_token *tokens);
bool	check_infile(t_token *token);
bool	check(t_token *token);
char	*here_doc(t_data *data, char *delimiter);
bool	check_delimiter(t_token *token);
bool	check_append(t_token *tokens);
bool	check_cmd(t_token *token);
bool	check_open(t_token *tokens);
bool	check_file(t_token *token, int *fd);
void	free_tab(char **str);
bool	check_access(t_data *data);
char	*check_exec(t_token *token, char **env);

/* ===========================
	Error Handling
	=========================== */
bool	print_error(char *str);
void	print_str_array(char **arr);

/* ===========================
	Process & Execution
	=========================== */
void	ft_child_infile(t_data *data, int fd_gen[2]);
void	ft_parent_outfile(t_data *data, int fd_gen[2]);
void	ft_child_cmd(t_token *token, char **env,
			int prev_pipe[2], int next_pipe[2]);
void	ft_parent_cmd(int prev_pipe[2]);
void	ft_exec(t_data *data);
int		pipe_number(t_data *data);
void	update_pipe_and_cmd(int prev_pipe[2], t_token *segment_end,
			t_token **cmd, int pipe_fd[2]);
bool	env(t_data *data, t_token *cmd);
int		find_outfile_fd(t_token *cmd);
int		get_pipe(t_data *data);
bool	do_builtin(t_data *data, t_token *token);
void	child_process(t_token *segment, int *prev_pipe,
			int *pipe_fd, t_data *data);
void	init_pipes(int *pipe_fd, int *has_pipe, t_token *segment_end);
t_token	*get_segment_end(t_token *start);
int		has_output_redirection(t_token *cmd);
char	**build_argv(t_token *cmd);
void	handle_redirections(t_token *cmd);
void	save_and_redirect_stdout(int fd, int *saved);
void	restore_stdout(int saved);
void	ft_replace_env(t_data *data, char *var, char *value);
bool	update_pwd_env(t_data *data, char *oldpwd);
t_token		*find_first_cmd(t_token *segment_start);

/* ===========================
	Command Path & Error
	=========================== */
char	*get_cmd_path(char *cmd, char **envp);
void	ft_error(const char *msg, const char *detail);

/* ===========================
	Heredoc & Signals
	=========================== */
void	prepare_heredocs(t_token *tokens);
int		do_heredoc(char *delimiter);
void	sigint_handler(int sig);

/* ===========================
	Command Utilities
	=========================== */
t_token	*find_command_token(t_token *start);
void	run_child_process(t_data *data, t_token *cmd, \
		int prev_pipe[2], int pipe_fd[2]);
void	exit_clean(t_data *data, char **argv, int status);
void	exit_perror(char *msg);
t_token	*find_cmd(t_token *segment_start);
void	move_command_to_front(t_token *segment_start);
int		copy_clean_var(char *dst, char *src, int i);
char	*simple_expend(t_data data, char *line, char *var, int i);

/* Token management functions */
t_token	*create_token(t_enum_token type, char *value);
void	free_tokens(t_token *token);
t_token	*create_token_from_value(char *token_value);

/* Token list functions */
bool	add_token_to_list(t_token **head, t_token **last, t_token *token);
void	print_token_list(t_token *head);
void	token_remove_quote(t_token *list);
void	access_token_cmd(t_token *list);

/* Parsing functions */
t_data	*parse_command(t_data *data, char *input);
t_token	*token(char *input);
void	add_token(char *token_value, t_enum_token type);

/* Quote handling functions */
bool	valid_quotes(char *line);
bool	check_quote_state(char *line, int pos, char c);
bool	in_any_quote(char *line, int pos);
int		quote_counter(char *line);
char	*quotes_remover(char *line);

/* Variable expansion functions */
char	*expend_vars(t_data data, char *line);
char	*modified_var(t_data data, char *var);
char	*cut_var(char *var);

/* Utility functions */
bool	is_separator(char c);
bool	is_quoted(char *str);
bool	is_builtin(t_token *token);

/* Input handling functions */
char	*input_with_space(char *str);
void	add_operator_with_spaces(char *new_input, char *input, int *i, int *j);

/* Environment functions */
//char	*get_path(char **envp);
//char	*ft_getenv(char *str, char **envp);

/* Built-in commands */
bool	ft_echo(t_data *data, t_token *token);
bool	ft_cd(t_data *data, t_token *token);
bool	ft_pwd(t_data *data, t_token *token);
bool	ft_export(t_data *data, t_token *token);
bool	ft_unset(t_data *data, t_token *token);
bool	ft_env(t_data *data, t_token *token);
bool	ft_exit(t_data *data, t_token *token);

t_data	*init_data(t_data *data, char **env);
void	free_data(t_data *data);

/* Cheking *Token */
bool	check_pipe(t_token *token);
bool	lexing(t_data *data);
bool	check_outfile(t_token *tokens);
void	print_token_list(t_token *head);
bool	check_infile(t_token *token);
bool	check(t_token *token);
char	*here_doc(t_data *data, char *delimiter);
bool	check_delimiter(t_token *token);
bool	check_append(t_token *tokens);
bool	check_cmd(t_token *token);
bool	check_open(t_token *tokens);
bool	check_file(t_token *token, int *fd);
void	free_tab(char **str);
bool	check_access(t_data *data);
char	*check_exec(t_token *token, char **env);
void	minishell_loop(t_data *data);

/* Error handling */
bool	print_error(char *str);
void	print_str_array(char **arr);
void	ft_child_infile(t_data *data, int fd_gen[2]);
void	ft_parent_outfile(t_data *data, int fd_gen[2]);
void	ft_child_cmd(t_token *token, char **env, int prev_pipe[2],
			int next_pipe[2]);
void	ft_parent_cmd(int prev_pipe[2]);

void	ft_exec(t_data *data);
int		pipe_number(t_data *data);
void	update_pipe_and_cmd(int prev_pipe[2], t_token *segment_end,
			t_token **cmd, int pipe_fd[2]);
bool	env(t_data *data, t_token *cmd);
int		find_outfile_fd(t_token *cmd);
int		get_pipe(t_data *data);
bool	do_builtin(t_data *data, t_token *token);
void	child_process(t_token *segment, int *prev_pipe,
			int *pipe_fd, t_data *data);
void	init_pipes(int *pipe_fd, int *has_pipe, t_token *segment_end);
t_token	*get_segment_end(t_token *start);
int		has_output_redirection(t_token *cmd);
char	**build_argv(t_token *cmd);
void	handle_redirections(t_token *cmd);
void	save_and_redirect_stdout(int fd, int *saved);
void	restore_stdout(int saved);
void	ft_replace_env(t_data *data, char *var, char *value);
bool	update_pwd_env(t_data *data, char *oldpwd);
// Déclaration de get_cmd_path
char	*get_cmd_path(char *cmd, char **envp);

// Déclaration de ft_error
void	ft_error(const char *msg, const char *detail);
void	free_data(t_data *data);
void	free_data_main(t_data *data);
void	prepare_heredocs(t_token *tokens);
int		do_heredoc(char *delimiter);
void	configure_signals(t_signal_mode mode);
t_token	*find_command_token(t_token *start);
void	run_child_process(t_data *data, t_token *cmd,
			int prev_pipe[2], int pipe_fd[2]);
void	exit_clean(t_data *data, char **argv, int status);
void	exit_perror(char *msg);
t_token	*find_cmd(t_token *segment_start);
void	move_command_to_front(t_token *segment_start);
int		copy_clean_var(char *dst, char *src, int i);
char	*simple_expend(t_data data, char *line, char *var, int i);
void	exec_loop(t_data *data);
pid_t	process_segment(t_data *data, t_token *start, int prev[2], int pipe[2]);
void	update_prev_pipe(int prev_pipe[2], int pipe_fd[2]);
void	exec_child(t_data *data, t_token *start, int prev_pipe[2], int pipe_fd[2]);
void	exec_dispatch(t_data *data, t_token *start);
void	exec_external(t_data *data, t_token *start);
void	exit_execve_errno(void);
void	setup_pipes_and_redirects(t_token *cmd, int prev[2], int fds[2]);

#endif
