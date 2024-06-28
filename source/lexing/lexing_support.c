/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_support.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 10:59:36 by aconceic          #+#    #+#             */
/*   Updated: 2024/06/28 16:42:32 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//mini_d->token->state != IN_QUOTE
void	find_env(t_mini *mini_d)
{
	t_token	*head;

	head = mini_d->token;
	while (mini_d->token)
	{
		if (mini_d->token->type == WORD && mini_d->token->state != 1
			&& mini_d->token->content[0] == '$'
			&& ft_isalnum(mini_d->token->content[1]))
			mini_d->token->type = ENV;
		mini_d->token = mini_d->token->next;
	}
	mini_d->token = head;
}

/**
 * @brief Define if a char is a special characther or not
 * @return False for normal, or enum number with the kind of the character
*/
int	specch(char ch)
{
	if (ch == '\'' || ch == '\"' || ch == '<' || ch == '>' || ch == '|'
		|| ch == '$' || ch == ' ' || ch == '\n' || ch == '\0')
	{
		if (ch == ' ')
			return (W_SPACE);
		else if (ch == '\"')
			return (D_QUOTE);
		else if (ch == '\'')
			return (S_QUOTE);
		else if (ch == '|')
			return (PIPE);
		else if (ch == '$')
			return (ENV);
		else if (ch == '>')
			return (R_OUT);
		else if (ch == '<')
			return (R_IN);
		else if (ch == '\0')
			return (424242);
	}
	return (0);
}

/**
 * @brief Create a token with values given from the function do_lexing
*/
int	create_token(t_mini *mini_d, char *input, int state, int len)
{
	t_token		*new_token;
	char		*content;
	static int	id;

	content = ft_strdup_qt(input, len);
	new_token = init_token(content, mini_d->token_type, id);
	if ((input[0] == '"' && state == 2) || (input[0] == '\'' && state == 1))
		state = 0;
	new_token->state = state;
	token_lstadd_back(mini_d, new_token);
	new_token->head = set_token_head(mini_d);
	new_token->tail = set_token_tail(mini_d);
	id ++;
	free(content);
	return (EXIT_SUCCESS);
}
