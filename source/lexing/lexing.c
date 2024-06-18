/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismirand <ismirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:17:04 by aconceic          #+#    #+#             */
/*   Updated: 2024/06/18 10:32:30 by ismirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		do_lexing(t_mini *mini_d);
void	do_lexing_aux(t_mini *mini_d, int *i, int *state);
int		specch(char ch);
int		create_token(t_mini *mini_d, char *input, int state, int len);
int		define_state(char ch, int state, int *i);

//special (|, >, <,>>,<<, $, ‘ ‘ )
//ft_strchr("|>$<" ,mini_d->input[i])
//tratar erro descentemente
//<< EOF ls -l | cat >output.txt
int	do_lexing(t_mini *mini)
{
	int	i;
	int	state;
	int	wrd_len;

	i = 0;
	state = 0;
	wrd_len = 0;
	while (mini->input[i])
	{
		if (specch(mini->input[i]))
		{
			do_lexing_aux(mini, &i, &state);
			i++;
		}
		else
		{
			mini->token_type = WORD;
			wrd_len = i;
			while (mini->input[i] && !specch(mini->input[i]))
				i ++;
			create_token(mini, &mini->input[wrd_len], state, (i - wrd_len));
		}
	}
	return (EXIT_SUCCESS);
}

void	do_lexing_aux(t_mini *mini_d, int *i, int *state)
{
	int	type;

	type = specch(mini_d->input[*i]);
	mini_d->token_type = type;
	if (type == D_QUOTE || type == S_QUOTE)
	{
		create_token(mini_d, &mini_d->input[*i], *state, 1);
		*state = define_state(mini_d->input[*i], *state, i);
	}
	if (type == W_SPACE || type == PIPE || type == ENV
		|| type == REDIR_OUT || type == REDIR_IN)
	{
		if ((type == REDIR_OUT && specch(mini_d->input[*i + 1]) == REDIR_OUT)
			|| (type == REDIR_IN && specch(mini_d->input[*i + 1]) == REDIR_IN))
		{
			if (type == REDIR_OUT)
				mini_d->token_type = D_REDIR_OUT;
			else
				mini_d->token_type = HEREDOC;
			create_token(mini_d, &mini_d->input[*i], *state, 2);
			(*i)++;
		}
		else
			create_token(mini_d, &mini_d->input[*i], *state, 1);
	}
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
			return (REDIR_OUT);
		else if (ch == '<')
			return (REDIR_IN);
	}
	return (false);
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

/**
 * @brief Define the state of a word. This means that, if is 
 * "word" -> state = DQUOTE, 'word' -> state = QUOTE, 
 * word -> state = general
*/
int	define_state(char ch, int state, int *i)
{
	if (ch == '\"')
	{
		if (state == 0)
			return (2);
		else if (state == 2)
			return (0);
	}
	if (ch == '\'')
	{
		if (state == 0)
			return (1);
		else if (state == 1)
			return (0);
	}
	(void)i;
	return (state);
}
