/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:37:31 by wailas            #+#    #+#             */
/*   Updated: 2025/04/30 16:43:20 by wailas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*create_token(t_enum_token type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
	{
		perror("Error\n");
		exit(EXIT_FAILURE);
	}
	token->type = type;
	token->value = ft_strdup(value);
	if (!token->value)
	{
		perror("Error\n");
		free(token);
		exit(EXIT_FAILURE);
	}
	return (token);
}

void	add_operator_with_spaces(char *new_input, char *input, int *i, int *j)
{
	if ((input[*i] == '<' && input[*i + 1] == '<') || (input[*i] == '>' && input[*i + 1] == '>'))
	{
		new_input[(*j)++] = ' ';
		new_input[(*j)++] = input[(*i)++];
		new_input[(*j)++] = input[(*i)++];
		new_input[(*j)++] = ' ';
	}
	else
	{
		new_input[(*j)++] = ' ';
		new_input[(*j)++] = input[(*i)++];
		new_input[(*j)++] = ' ';
	}
}

char	*input_with_space(char *input)
{
	int		i = 0;
	int		j = 0;
	char	*new_input;

	if (!input)
		return (NULL);
	new_input = malloc(strlen(input) * 3 + 1);
	if (!new_input)
		return (NULL);

	while (input[i])
	{
		if ((input[i] == '<' || input[i] == '>' || input[i] == '|') && in_any_quote(input, i) == 0)
			add_operator_with_spaces(new_input, input, &i, &j);
		else
			new_input[j++] = input[i++];
	}
	new_input[j] = '\0';
	return (new_input);
}


bool	is_quoted(char *str)
{
	while (*str)
	{
		if (*str == '\'' || *str == '"')
			return (true);
		str++;
	}
	return (false);
}

t_token	*create_token_from_value(char *token_value)
{
	if (!is_quoted(token_value))
	{
		if (ft_strcmp(token_value, "|") == 0)
			return (create_token(PIPE, token_value));
		if (ft_strcmp(token_value, ">>") == 0)
			return (create_token(APPEND, token_value));
		if (ft_strcmp(token_value, ">") == 0)
			return (create_token(REDIR_OUT, token_value));
		if (ft_strcmp(token_value, "<<") == 0)
			return (create_token(DELIMITEUR, token_value));
		if (ft_strcmp(token_value, "<") == 0)
			return (create_token(REDIR_IN, token_value));
	}
	return (create_token(ARG, token_value));
}
