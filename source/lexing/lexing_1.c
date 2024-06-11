/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismirand <ismirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:17:04 by aconceic          #+#    #+#             */
/*   Updated: 2024/06/11 19:36:08 by ismirand         ###   ########.fr       */
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
			if (is_space(mini_d->input[i]) || is_pipe(mini_d->input[i])
				|| is_env(mini_d->input[i]))
				create_token(mini_d, &mini_d->input[i], state, 1);
			if (is_redir_out(mini_d->input[i]) || is_redir_in(mini_d->input[i]))
			{
				if (is_redir_out(mini_d->input[i + 1]) || is_redir_in(mini_d->input[i + 1]))
					create_token(mini_d, &mini_d->input[i++], state, 2);
				else
					create_token(mini_d, &mini_d->input[i], state, 1);
			}
			i++;
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
 * "word" = WORD,
 * " " = W_SPACE,
 * "\"" = D_QUOTE,
 * "\'" = S_QUOTE,
 * "|" = PIPE,
 * "$" = ENV,
 * ">" = REDIR_OUT,
 * ">>" = D_REDIR_OUT.
 * "<" = REDIR_IN,
 * "<<" = HEREDOC,
*/
int	get_token_type(char *input)
{
	int	i;

	i = 0;
	if (is_space(input[0]))
		return (W_SPACE);
	else if (is_dquote(input[0]))
		return (D_QUOTE);
	else if (is_quote(input[0]))
		return (S_QUOTE);
	else if (is_pipe(input[0]))
		return (PIPE);
	else if (is_env(input[0]))
		return (ENV);
	else if (is_redir_out(input[0]) && !is_redir_out(input[1]))
		return (REDIR_OUT);
	else if (is_redir_out(input[0]) && is_redir_out(input[1]))
		return (D_REDIR_OUT);
	else if (is_redir_in(input[0]) && !is_redir_in(input[1]))
		return (REDIR_IN);
	else if (is_redir_in(input[0]) && is_redir_in(input[1]))
		return (HEREDOC);
	while (!is_special_char(input[i]))
		i ++;
	return (WORD);
}

