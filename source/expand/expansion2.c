/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismirand <ismirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:51:03 by aconceic          #+#    #+#             */
/*   Updated: 2024/09/06 14:53:57 by ismirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @attention Secondary function for find_expansion()
 * @brief Cleans the excess of white spaces token
*/
void	clean_token(t_mini *mini_d)
{
	t_token	*tmp;
	t_token	*prev;

	while (mini_d->token && mini_d->token->type == W_SPACE)
	{
		tmp = mini_d->token->next;
		free(mini_d->token->content);
		free(mini_d->token);
		mini_d->token = tmp;
	}
	prev = mini_d->token;
	tmp = mini_d->token;
	while (tmp)
	{
		if ((tmp->type == W_SPACE && prev->type == W_SPACE))
		{
			prev->next = tmp->next;
			free(tmp->content);
			free(tmp);
			tmp = prev;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

//amauri > $po TEST
//This is to update the type from word to file if find a redirect
void	update_word_to_file(t_mini *mini_d)
{
	t_token	*head;

	head = mini_d->token;
	while (mini_d->token)
	{
		if (mini_d->token->type == R_IN || mini_d->token->type == R_OUT
			|| mini_d->token->type == D_R_OUT || mini_d->token->type == HEREDOC)
		{
			if ((mini_d->token->len == 1 || mini_d->token->len == 2)
				&& (mini_d->token->next))
			{
				while ((mini_d->token->next->next)
					&& (mini_d->token->next->type != WORD
						&& mini_d->token->next->type != ENV))
					mini_d->token = mini_d->token->next;
				mini_d->token->next->type = FILE_NAME;
			}
		}
		mini_d->token = mini_d->token->next;
	}
	mini_d->token = head;
}

/**
 * @attention Secondary function for find_expansion()
 * @brief Cleans the excess of white spaces token
 * 0 for WORD, 5 for ENV
*/
void	assemble_word_tokens(t_mini *mini_d)
{
	t_token	*tmp;
	t_token	*prev;

	prev = NULL;
	tmp = mini_d->token;
	while (tmp && tmp->next)
	{
		if ((tmp->type == WORD || tmp->type == ENV)
			&& (tmp->next->type == WORD || tmp->next->type == ENV)
			&& (tmp->next->len > 0))
			assemble_word_tokens_aux(tmp);
		else
		{
			prev = tmp;
			tmp = tmp->next;
		}
	}
	(void)prev;
}

void	assemble_word_tokens_aux(t_token *tmp)
{
	char	*c_tmp;
	t_token	*to_free;

	c_tmp = ft_strdup(tmp->content);
	free(tmp->content);
	tmp->content = ft_strjoin(c_tmp, tmp->next->content);
	tmp->len = ft_strlen(tmp->content);
	tmp->type = tmp->next->type;
	free(c_tmp);
	to_free = tmp->next;
	tmp->next = tmp->next->next;
	free(to_free->content);
	free(to_free);
}
