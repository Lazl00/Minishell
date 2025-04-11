/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 16:49:35 by lcournoy          #+#    #+#             */
/*   Updated: 2025/04/11 19:05:07 by wailas           ###   ########.fr       */
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

t_token	*create_token(t_enum_token type, const char *value);
void	free_token(t_token *token);
char	*input_with_space(const char *str);
void	add_token(const char *token_value, t_enum_token type);
void	parse_command(const char *input);
char	*handle_quotes(const char *str);

#endif
