/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismirand <ismirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 15:40:12 by aconceic          #+#    #+#             */
/*   Updated: 2024/06/11 17:23:38 by ismirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token *init_token(char *content, e_token type, int id)
{
    t_token *new_token = malloc(sizeof(t_token));
    if (new_token == NULL)
	{
    	return NULL; // Handle error: memory allocation failed
	}

	new_token->id = id;
    new_token->len = ft_strlen(content);
    new_token->content = ft_strdup(content);
    new_token->next = NULL;
    new_token->type = type;
    new_token->head = NULL;
    new_token->tail = NULL;

    return new_token;
}

int token_lstadd_back(t_mini *mini_d, t_token *new_token)
{
    t_token *node;

    if (mini_d->token == NULL)
    {
        mini_d->token = new_token;
        return (EXIT_SUCCESS);
    }
    else
    {
        node = mini_d->token;
        while (node->next != NULL)
            node = node->next;
        node->next = new_token;
    }
    return (EXIT_SUCCESS);
}

//ATTENTION -> need to refine error mngmt
t_token	*set_token_head(t_mini *mini_d)
{
	if (!mini_d->token)
	{
		printf("set_token_head\n");	
		return (NULL);
	}
	return (mini_d->token);
}

//ATTENTION -> need to refine error mngmt
t_token *set_token_tail(t_mini *mini_d)
{
	t_token *current;

	if (!mini_d->token)				
		return (NULL);
			
	current = mini_d->token;
	while(current->next != NULL)
		current = current->next;
	return (current);
}

//dont forget to clean this (THIS IS GIVING MEMORY LEAK)
int	alloc_tokenstruct(t_mini *mini_d)
{
	mini_d->token = malloc(sizeof(t_token));
	mini_d->token->head = malloc(sizeof(t_token));
	if (!mini_d->token || !mini_d->token->head )
	{
		printf("error alloc_tokenstruct\n");
		return (EXIT_FAILURE);
	}
	memset(mini_d->token, 0, sizeof(t_token));

	return (EXIT_SUCCESS);
}
