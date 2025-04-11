/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 18:47:32 by wailas            #+#    #+#             */
/*   Updated: 2025/04/11 18:49:59 by wailas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	parse_command(const char *input)
{
	char	*input_copy;
	char	*token_value;
	t_token	*token;
	char	*quote_handle_quote;

	quote_handle_quote = handle_quotes(input);
	input_copy = input_with_space(quote_handle_quote);
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
		printf("Token: %s | Type: %d\n", token->value, token->type);
		free_token(token);
		token_value = ft_strtok(NULL, " \t\n");
	}
	free(input_copy);
}
