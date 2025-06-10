/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:28:04 by lcournoy          #+#    #+#             */
/*   Updated: 2025/06/04 14:27:32 by wailas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_numeric(char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	if (!*str)
		return (false);
	while (*str)
	{
		if (!isdigit(*str))
			return (false);
		str++;
	}
	return (true);
}

bool	ft_exit(t_data *data, t_token *token)
{
	int	code;

	code = 0;
	if (!data || !token)
		return (false);
	printf("exit\n");
	if (token->next && token->next->type == ARG)
	{
		if (!is_numeric(token->next->value))
		{
			write(2, "minishell: numeric argument required\n", 38);
			free_data(data);
			exit(2);
		}
		code = ft_atoi(token->next->value);
		if (token->next->next && token->next->next->type == ARG)
		{
			write(2, "minishell: exit: too many arguments\n", 37);
			return (false);
		}
	}
	free_data(data);
	exit((unsigned char)code);
}
