/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcournoy <lcournoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:25:57 by lcournoy          #+#    #+#             */
/*   Updated: 2025/04/22 17:58:57 by lcournoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_separator(char c)
{
	if (c >= 'a' && c <= 'z')
		return (false);
	if (c >= 'A' && c <= 'Z')
		return (false);
	if (c >= '0' && c <= '9')
		return (false);
	if (c == '_')
		return (false);
	return (true);
}

char	*modified_var(t_data data, char	*var)
{
	int	line;
	int	i;
	
	line = 0;
	i = 0;
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

char    *simple_expend(t_data data, char *line, char *var)
{
	char	*new_var;
	char	*clean_var;
	char	*new_line;
	int i;
	int j;
	
	j = 0;
	i = 0;
	new_line = NULL;
	if (*(var + 1) == '\0' || is_separator(*(var + 1)))
	{
		new_line = malloc(sizeof(char) + 2);
		while (line < var)
			new_line[i++] = *line++;
		new_line[i++] = '$';
		line++;
		while (*line)
			new_line[i++] = *line++;
		new_line[i] = '\0';
		return (new_line);
	}
	new_var = cut_var(++var);
	clean_var = modified_var(data, new_var);
	new_line = malloc(ft_strlen(line) - ft_strlen(new_var) + ft_strlen(clean_var));
	while (line < var)
	{
		new_line[i] = *line;
		line++;
		i++;
	}
	line += ft_strlen(new_var);
	i--;
	if (clean_var)
	{	
		while (clean_var[j])
		{
			new_line[i] = clean_var[j];
			j++;
			i++;
		}
	}
	while (*line)
	{
		new_line[i] = *line;
		line++;
		i++;
	}
	new_line[i] = '\0';
	return (new_line);
}

char	*expend_vars(t_data data, char *line)
{
    int     i;
    char    *expended_line;
	char	*tmp;

	tmp = line;
    i = 0;
    while (line[i])
    {
        if (line[i] == '$' && check_quote_state(line, i, '\'') == 0)
        {
            expended_line = simple_expend(data, line, &line[i]);
			free(line);
			line = ft_strdup(expended_line);
			free(expended_line);
        }
		i++;
	}
	return (line);
}

// si pas de suite a "$"							->	affiche le '$'
// si pas de var correspondantes a la suite de $	->	affiche rien

// actuellement les deux cas SIGSEGV