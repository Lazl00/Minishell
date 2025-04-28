/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 16:49:35 by lcournoy          #+#    #+#             */
/*   Updated: 2025/04/28 15:10:40 by wailas           ###   ########.fr       */
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
	token_cmd,
	token_redir_in,
	token_redir_out,
	token_pipe,
	token_outfile,
	token_infile,
	token_delimiteur,
	token_append,
	token_arg
}	t_enum_token;

typedef struct s_token {
	char			*value;
	t_enum_token	type;
}	t_token;

typedef struct s_data {
	char	**env;
	t_token	*tokens;
	char	*path;
	int		fd[2];
}	t_data;

t_token	*create_token(t_enum_token type, char *value);
void	free_token(t_token *token);
char	*input_with_space(char *str);
void	add_token(char *token_value, t_enum_token type);
void	parse_command(t_data data, char *input);
bool	valid_quotes(char *line);
bool	check_quote_state(char *line, int pos, char c);
char	*expend_vars(t_data data, char *line);
char	*simple_expend(t_data data, char *line, char *var);
char	*get_path(char **envp);
char	*ft_getenv(char *str, char **envp);
char	*modified_var(t_data data, char	*var);
bool	is_separator(char c);
char	*cut_var(char *var);
int		ft_echo(char *av);
int		ft_exec(char *line);
bool	token(char *input);

#endif
