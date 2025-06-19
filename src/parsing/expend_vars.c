/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:25:57 by lcournoy          #+#    #+#             */
/*   Updated: 2025/06/04 14:19:22 by wailas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*modified_var(t_data data, char	*var)
{
	int	line;
	int	i;

	line = 0;
	i = 0;
	if (var[0] == '?')
		return (ft_itoa(data.exit_status));
	while (data.env[line])
	{
		while (data.env[line][i] == var[i])
		{
			i++;
			if (!var[i] && data.env[line][i] == '=')
				return (&data.env[line][++i]);
		}
		i = 0;
		line++;
	}
	return (NULL);
}

char	*cut_var(char *var)
{
	int		i;
	char	*cropped_var;

	i = 0;
	if (var[0] == '?')
	{
		cropped_var = malloc(2);
		cropped_var[0] = '?';
		cropped_var[1] = '\0';
		return (cropped_var);
	}
	while (var[i] && is_separator(var[i]) == false)
		i++;
	cropped_var = malloc(i + 1);
	i = 0;
	while (var[i] && is_separator(var[i]) == false)
	{
		cropped_var[i] = var[i];
		i++;
	}
	cropped_var[i] = '\0';
	return (cropped_var);
}

char	*simple_expend(t_data data, char *line, char *var, int i)
{
	char	*new_var;
	char	*clean_var;
	char	*new_line;
	int		j;

	j = 0;
	if (*(var + 1) == '\0' || is_separator(*(var + 1)))
		return (NULL);
	new_var = cut_var(++var);
	clean_var = modified_var(data, new_var);
	new_line = malloc(len(line) - len(new_var) + len(clean_var));
	while (line < var)
		new_line[i++] = *line++;
	line += len(new_var);
	i--;
	if (clean_var)
		while (clean_var[j])
			new_line[i++] = clean_var[j++];
	while (*line)
		new_line[i++] = *line++;
	new_line[i] = '\0';
	if (*new_var == '?')
		free(clean_var);
	free(new_var);
	return (new_line);
}

char	*expend_vars(t_data data, char *line, int i, int i_diff)
{
	char	*expended_line;
	char	*dupped_str;

	expended_line = NULL;
	while (line[i])
	{
		if (line[i] == '$' && check_quote_state(line, i, '\'') == 0)
		{
			if (is_heredoc(line, i) == false)
				expended_line = simple_expend(data, line, &line[i], i_diff);
			if (expended_line)
			{
				free(line);
				line = expended_line;
			}
			else
				i++;
		}
		else
			i++;
	}
	dupped_str = ft_strdup(line);
	free(line);
	return (dupped_str);
}

bool	is_heredoc(char	*line, int i)
{
	if (i < 2)
		return (false);
	i--;
	while (i >= 0 && line[i] == ' ')
		i--;
	if (i > 0 && line[i] == '<' && line[i - 1] == '<')
	{
		if (check_quote_state(line, i, '\'') == false)
		{
			return (true);
		}
	}
	return (false);
}
