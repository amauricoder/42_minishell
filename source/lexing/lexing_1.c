/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:17:04 by aconceic          #+#    #+#             */
/*   Updated: 2024/06/08 19:55:46 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//special (|, >, <,>>,<<, $, ‘ ‘ )
//ft_strchr("|>$<" ,mini_d->input[i])
int do_lexing(t_mini *mini_d)
{
	int	i;
	int state;
	int word_len;

	i = 0;
	state = 0;
	word_len = 0;
	while(mini_d->input[i])
	{
		if (is_special_char(mini_d->input[i]))
		{
			if (is_dquote(mini_d->input[i]) || is_quote(mini_d->input[i]))
			{
				create_token(mini_d, &mini_d->input[i], state, 1);
				state = define_state(mini_d->input[i], state, &i);
			}
			if (is_space(mini_d->input[i]))
				create_token(mini_d, &mini_d->input[i], state, 1);
			i ++;
		}
		else
		{
			//aqui eu busco a palavra e salvo em um token
			word_len = i;
			while(!is_special_char(mini_d->input[i]))
			{
				printf("%c \n", mini_d->input[i]);
				i ++;
			}
			//tratar erro descentemente
			create_token(mini_d, &mini_d->input[word_len], state, (i - word_len));
		}
	}
	return (EXIT_SUCCESS);
}

/**
 * @brief Create a token with values given from the function do_lexing
*/
int	create_token(t_mini *mini_d, char *input, int state, int len)
{
	t_token *new_token;
	char	*content;
	static int id;

	content = ft_strdup_qt(input, len);
	new_token = init_token(content, get_token_type(content), id);
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

/**
 * @brief Define the state of a word. This means that, if is "word" -> state = DQUOTE,
 * 'word' -> state = QUOTE, word -> state = general
*/
int	define_state(char ch, int state, int *i)
{
	if (is_dquote(ch))
    {
        if (state == 0)
            return (2);
        else if (state == 2)
    		return (0);
    }
	if (is_quote(ch))
	{
		if (state == 0)
			return (1);
		else if (state == 1)
			return (0);
	}
	(void)i;
    return state;
}

/**
 * @brief Check the type of the token.
 * " " = SPACE,
 * "\"" = DQUOTE,
 * "word" = WORD
*/
int	get_token_type(char *input)
{
	int	i;

	if (is_dquote(input[0]) || is_dquote(input[1]))
		return (DQUOTE);
	else if (is_space(input[0]))
		return (WHITE_SPACE);

	i = 0;
	while (!is_special_char(input[i]))
		i ++;
	return (WORD);
}

