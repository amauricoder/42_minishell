/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 15:40:12 by aconceic          #+#    #+#             */
/*   Updated: 2024/09/12 18:46:57 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @attention Secondary function for create_token.
 * @brief Malloc and init values for a token.
*/
t_token	*init_token(char *content, int type, int id)
{
	t_token	*new_token;

	new_token = ft_calloc(sizeof(t_token), 1);
	if (new_token == NULL)
		return (NULL);
	new_token->id = id;
	new_token->len = ft_strlen(content);
	new_token->content = ft_strdup(content);
	new_token->next = NULL;
	new_token->prev = NULL;
	new_token->type = type;
	new_token->head = NULL;
	new_token->tail = NULL;
	return (new_token);
}

/**
 * @attention Secondary function for create_token.
 * @brief Add the token to the end of the linked list. Set prev pointer.
*/
int	token_lstadd_back(t_mini *mini_d, t_token *new_token)
{
	t_token	*node;

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
		new_token->prev = node;
	}
	return (EXIT_SUCCESS);
}

/**
 * @attention Secondary function for create_token.
 * @brief Set the head of the linked list.
*/
t_token	*set_token_head(t_mini *mini_d)
{
	if (!mini_d->token)
	{
		err_msg(mini_d, "Error setting token head\n", 127, 0);
		return (NULL);
	}
	return (mini_d->token);
}

/**
 * @attention Secondary function for create_token.
 * @brief Set the tail(last token) of the linked list.
*/
t_token	*set_token_tail(t_mini *mini_d)
{
	t_token	*current;

	if (!mini_d->token)
	{
		err_msg(mini_d, "Error setting token tail\n", 127, 0);
		return (NULL);
	}
	current = mini_d->token;
	while (current->next != NULL)
		current = current->next;
	return (current);
}
