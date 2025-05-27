/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:37:31 by wailas            #+#    #+#             */
/*   Updated: 2025/05/27 13:23:21 by wailas           ###   ########.fr       */
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
	token->heredoc_fd = -1;
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
	if ((input[*i] == '<' && input[*i + 1] == '<') || \
	(input[*i] == '>' && input[*i + 1] == '>'))
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
	int		i;
	int		j;
	char	*new_input;

	i = 0;
	j = 0;
	if (!input)
		return (NULL);
	new_input = malloc(strlen(input) * 3 + 1);
	if (!new_input)
		return (NULL);
	while (input[i])
	{
		if ((input[i] == '<' || input[i] == '>' || input[i] == '|') \
		&& in_any_quote(input, i) == 0)
			add_operator_with_spaces(new_input, input, &i, &j);
		else
			new_input[j++] = input[i++];
	}
	new_input[j] = '\0';
	return (new_input);
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

t_token	*token(char *input)
{
	char			*input_copy;
	char			*token_value;
	t_token			*new_token;
	t_token			*head;
	t_token			*last;

	last = NULL;
	head = NULL;
	input_copy = input_with_space(input);
	if (!input_copy)
		return (NULL);
	token_value = ft_strtok(input_copy, " \t\n");
	while (token_value)
	{
		new_token = create_token_from_value(token_value);
		if (!add_token_to_list(&head, &last, new_token))
			return (NULL);
		token_value = ft_strtok(NULL, " \t\n");
	}
	free(input_copy);
	token_remove_quote(head);
	return (head);
}
