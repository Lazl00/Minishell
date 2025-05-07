/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 16:49:35 by lcournoy          #+#    #+#             */
/*   Updated: 2025/05/07 14:53:23 by wailas           ###   ########.fr       */
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
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/include/libft.h"
# include "../libft/include/ft_printf.h"
# include "../libft/include/get_next_line.h"

typedef enum s_quote {
	outside,
	inside_single_quote,
	inside_double_quote
}	t_enum_quote;

typedef enum s_token_parse {
	CMD,
	REDIR_IN,
	REDIR_OUT,
	PIPE,
	OUTFILE,
	INFILE,
	DELIMITEUR,
	APPEND,
	ARG
}	t_enum_token;

typedef struct s_token {
	char			*value;
	t_enum_token	type;
	struct s_token	*next;
}	t_token;

typedef struct s_env {
	char		*alias;
	char		*def;
	struct s_env	*next;
}	t_env;

typedef struct s_data {
	char	**env;
	t_token	*tokens;
	char	*path;
	int		fd[2];
}	t_data;

/* Token management functions */
t_token         *create_token(t_enum_token type, char *value);
void            free_token(t_token *token);
t_token         *create_token_from_value(char *token_value);

/* Token list functions */
bool            add_token_to_list(t_token **head, t_token **last, t_token *token);
void            print_token_list(t_token *head);
void            token_remove_quote(t_token *list);
void            access_token_cmd(t_token *list);

/* Parsing functions */
t_data		*parse_command(t_data *data, char *input);
t_token    *token(char *input);
void            add_token(char *token_value, t_enum_token type);

/* Quote handling functions */
bool            valid_quotes(char *line);
bool            check_quote_state(char *line, int pos, char c);
bool            in_any_quote(char *line, int pos);
int             quote_counter(char *line);
char            *quotes_remover(char *line);

/* Variable expansion functions */
char            *expend_vars(t_data data, char *line);
char            *simple_expend(t_data data, char *line, char *var);
char            *modified_var(t_data data, char *var);
char            *cut_var(char *var);

/* Utility functions */
bool            is_separator(char c);
bool            is_quoted(char *str);
bool            is_builtin(char *cmd);

/* Input handling functions */
char            *input_with_space(char *str);
void            add_operator_with_spaces(char *new_input, char *input, int *i, int *j);

/* Environment functions */
char            *get_path(char **envp);
char            *ft_getenv(char *str, char **envp);

/* Built-in commands */
int             ft_echo(char *av);
int             ft_exec(char *line);
t_data			*init_data(t_data *data, char **env);
void	free_data(t_data *data);

#endif
