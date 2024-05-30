/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:17:04 by aconceic          #+#    #+#             */
/*   Updated: 2024/05/30 18:13:23 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//special (|, >, <,>>,<<, $, ‘ ‘ )
int do_lexing(t_mini *mini_d)
{
	int	i;

	i = 0;
	while(mini_d->input[i])
	{
		printf("%c\n", mini_d->input[i]);
		if (is_space(mini_d->input[i]))
		{	
			init_token(mini_d, " ", WHITE_SPACE);
		}
		i ++;
	}
	return (EXIT_SUCCESS);
}


int	is_quote(char ch)
{
	if (ch == 39)
		return (1);
	else
		return (0);
}

int	is_space(char ch)
{
	if (ch == ' ')
		return (1);
	else
		return (0);
}

int	init_token(t_mini *mini_d, char *content, e_token type)
{
	//dont forget to clean alloc_tokenstruct
	alloc_tokenstruct(mini_d);
	mini_d->token->len = ft_strlen(content);
	mini_d->token->content = ft_strdup(content);
	mini_d->token->type = type;
	return (EXIT_SUCCESS);
}

//dont forget to clean this (THIS IS GIVING MEMORY LEAK)
int	alloc_tokenstruct(t_mini *mini_d)
{
	mini_d->token = malloc(sizeof(t_token));
	mini_d->token->head = malloc(sizeof(t_token));
	mini_d->token->tail = malloc(sizeof(t_token));
	mini_d->token->next = malloc(sizeof(t_token));
	mini_d->token->prev = malloc(sizeof(t_token));
	if (!mini_d->token || !mini_d->token->head || !mini_d->token->tail
			|| !mini_d->token->next || !mini_d->token->prev)
	{
		return (EXIT_FAILURE);
	}
	memset(mini_d->token, 0, sizeof(t_token));

	return (EXIT_SUCCESS);
}