/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:37:31 by wailas            #+#    #+#             */
/*   Updated: 2025/04/10 13:54:52 by wailas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*create_token(t_enum_token type, const char *value)
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

void	free_token(t_token *token)
{
	if (token)
	{
		free(token->value);
		free(token);
	}
}

int	before_space(const char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '|' || str[i] == '>' || str[i] == '<')
		{
			count += 3;
			i++;
		}
		else
		{
			count++;
			i++;
		}
	}
	return (count);
}

char	*input_with_space(const char *str)
{
	int		i;
	int		j;
	int		length;
	char	*result;

	i = 0;
	j = 0;
	length = before_space(str);
	result = malloc(sizeof(char) * (length + 1));
	while (str[i])
	{
		if (str[i] == '|' || str[i] == '>' || str[i] == '<')
		{
			result[j++] = ' ';
			result[j++] = str[i++];
			result[j++] = ' ';
		}
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}

void	parse_command(const char *input)
{
	char	*input_copy;
	char	*token_value;
	t_token	*token;

	input_copy = input_with_space(input);
	token_value = ft_strtok(input_copy, " \t\n");
	if (!token_value)
	{
		free(input_copy);
		return ;
	}
	while (token_value != NULL)
	{
		if (ft_strcmp(token_value, "|") == 0)
			token = create_token(token_pipe, token_value);
		else if (ft_strcmp(token_value, ">") == 0)
			token = create_token(token_redir_out, token_value);
		else if (ft_strcmp(token_value, "<") == 0)
			token = create_token(token_redir_in, token_value);
		else
			token = create_token(token_arg, token_value);
		free_token(token);
		token_value = ft_strtok(NULL, " \t\n");
	}
	free(input_copy);
}
