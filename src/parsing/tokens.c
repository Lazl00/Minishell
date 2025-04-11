/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:37:31 by wailas            #+#    #+#             */
/*   Updated: 2025/04/11 18:50:42 by wailas           ###   ########.fr       */
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
