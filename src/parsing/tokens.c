/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:37:31 by wailas            #+#    #+#             */
/*   Updated: 2025/04/29 16:53:45 by wailas           ###   ########.fr       */
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

int	before_space(char *str)
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

char	*input_with_space(char *str)
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
		if ((str[i] == '|' || str[i] == '>' || str[i] == '<') \
				&& ((check_quote_state(&str[i], i, '\'') == 0) \
					|| (check_quote_state(&str[i], i, '\"') == 0)))
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

bool token(char *input)
{
	char			*input_copy;
	char			*token_value;
	t_token			*new_token;
	t_token_node	*head = NULL;
	t_token_node	*last = NULL;
	t_token_node	*new_node;
	int				i;
	int				quotes;

	input_copy = input_with_space(input);
	if (!input_copy)
		return (false);
	token_value = ft_strtok(input_copy, " \t\n");
	while (token_value != NULL)
	{
		quotes = 0;
		i = 0;
		while (token_value[i])
		{
			if (token_value[i] == '\'' || token_value[i] == '"')
				quotes = 1;
			i++;
		}
		if (quotes == 0)
		{
			if (ft_strcmp(token_value, "|") == 0)
				new_token = create_token(token_pipe, token_value);
			else if (ft_strcmp(token_value, ">") == 0)
				new_token = create_token(token_redir_out, token_value);
			else if (ft_strcmp(token_value, "<") == 0)
				new_token = create_token(token_redir_in, token_value);
			else
				new_token = create_token(token_arg, token_value);
		}
		else
			new_token = create_token(token_arg, token_value);
		new_node = malloc(sizeof(t_token_node));
		new_node->token = new_token;
		new_node->next = NULL;
		if (!head)
			head = new_node;
		else
			last->next = new_node;
		last = new_node;

		token_value = ft_strtok(NULL, " \t\n");
	}
	free(input_copy);
	token_remove_quote(head);
	access_token_cmd(head);
	t_token_node *tmp = head;
	while (tmp)
	{
		ft_printf("Token : %s | Type : %d\n", tmp->token->value, tmp->token->type);
		tmp = tmp->next;
	}
	return (true);
}

