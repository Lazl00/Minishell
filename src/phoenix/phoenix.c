/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phoenix.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:00:57 by lcournoy          #+#    #+#             */
/*   Updated: 2025/05/28 23:36:42 by wailas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Ajoute un token à la fin d'une liste chaînée
void append_token(t_token **head, t_token *to_add)
{
    if (!to_add)
        return;
    to_add->next = NULL;
    if (!*head)
    {
        *head = to_add;
        return;
    }
    t_token *cur = *head;
    while (cur->next)
        cur = cur->next;
    cur->next = to_add;
}

// Ajoute tous les tokens trouvés par la fonction finder à la liste phoenix
void add_all_matching_tokens(t_token **phoenix, t_token **deprecated, t_token *(*finder)(t_token **))
{
    t_token *to_add;
    while ((to_add = finder(deprecated)))
        append_token(phoenix, to_add);
}

// Trouve et extrait le premier token de type donné dans deprecated
t_token *find_next_token_of_type(t_token **deprecated, t_enum_token type)
{
    t_token *cur = *deprecated;
    t_token *prev = NULL;

    while (cur)
    {
        if (cur->type == type)
        {
            if (prev)
                prev->next = cur->next;
            else
                *deprecated = cur->next;
            cur->next = NULL;
            return cur;
        }
        prev = cur;
        cur = cur->next;
    }
    return NULL;
}

// Fonctions spécifiques pour trouver les tokens par type (extraction de deprecated)
t_token *find_cmd_phoenix(t_token **deprecated)
{
    return find_next_token_of_type(deprecated, ARG);
}

t_token *find_pipe_phoenix(t_token **deprecated)
{
    return find_next_token_of_type(deprecated, PIPE);
}

t_token *find_arg_phoenix(t_token **deprecated)
{
    return find_next_token_of_type(deprecated, ARG);
}

t_token *find_infile_signe_phoenix(t_token **deprecated)
{
    return find_next_token_of_type(deprecated, REDIR_IN);
}

t_token *find_infile_phoenix(t_token **deprecated)
{
    return find_next_token_of_type(deprecated, ARG);
}

t_token *find_outfile_signe_phoenix(t_token **deprecated)
{
    return find_next_token_of_type(deprecated, REDIR_OUT);
}

t_token *find_outfile_phoenix(t_token **deprecated)
{
    return find_next_token_of_type(deprecated, ARG);
}

// Fonction principale pour reconstruire la liste phoenix
t_token *phoenix(t_token **deprecated)
{
    t_token *phoenix = NULL;
    t_token *to_add;

    while (1)
    {
        to_add = find_cmd_phoenix(deprecated);
        if (!to_add)
            break;
        append_token(&phoenix, to_add);

        add_all_matching_tokens(&phoenix, deprecated, find_arg_phoenix);
        add_all_matching_tokens(&phoenix, deprecated, find_infile_signe_phoenix);
        add_all_matching_tokens(&phoenix, deprecated, find_infile_phoenix);
        add_all_matching_tokens(&phoenix, deprecated, find_outfile_signe_phoenix);
        add_all_matching_tokens(&phoenix, deprecated, find_outfile_phoenix);

        to_add = find_pipe_phoenix(deprecated);
        if (!to_add)
            break;
        append_token(&phoenix, to_add);
    }
    return phoenix;
}

