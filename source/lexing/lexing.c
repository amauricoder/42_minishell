/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:17:04 by aconceic          #+#    #+#             */
/*   Updated: 2024/09/04 20:10:54 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Main function to lexind functionality.
 * Check char by char to identify special char. If it is, go to 2dary function.
 * if not, create the token of the word.
 * defines also the state of the token.
*/
int	do_lexing(t_mini *mini)
{
	int	i;
	int	state;
	int	wrd_len;

	i = 0;
	wrd_len = 0;
	while (mini->input[i])
	{
		state = GENERAL;
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
	define_type_env(mini);
	return (EXIT_SUCCESS);
}

/**
 * @brief Analyzes the current character in the 
 * input string to create the token according to the necessary type.
*/
void	do_lexing_aux(t_mini *mini_d, int *i, int *state)
{
	int	type;

	type = specch(mini_d->input[*i]);
	mini_d->token_type = type;
	if (type == S_QUOTE)
		in_quote(mini_d, i, state, 's');
	else if (type == D_QUOTE)
		in_quote(mini_d, i, state, 'd');
	else
	{
		redir_env(mini_d, i, state, type);
		if (*state == GENERAL && type == W_SPACE)
			while (specch(mini_d->input[*i + 1]) == W_SPACE)
				(*i)++;
	}
}

/**
 * @brief Secondary Function for do_lexing_aux.
 * for creation of the token of <, <<, >, >>, $.
*/
void	redir_env(t_mini *mini_d, int *i, int *state, int type)
{
	if ((type == R_OUT && specch(mini_d->input[*i + 1]) == R_OUT)
		|| (type == R_IN && specch(mini_d->input[*i + 1]) == R_IN)
		|| type == ENV)
	{
		if (type == ENV && mini_d->input[*i + 1] == '?')
		{
			create_token(mini_d, &mini_d->input[*i], *state, 2);
			(*i)++;
		}
		else
			in_special(mini_d, i, state, type);
	}
	else
		create_token(mini_d, &mini_d->input[*i], *state, 1);
}

/**
 * @brief Secondary Function for do_lexing_aux.
 * for creation of the token of ''.
*/
int	in_quote(t_mini *mini, int *i, int *state, char flag)
{
	int	wrd_len;

	wrd_len = 0;
	(*i)++;
	if (flag == 's')
	{
		*state = IN_QUOTE;
		if (mini->input[*i] == '\'')
			return (create_empty_token(mini, "", state, 2));
	}
	else if (flag == 'd')
	{
		*state = IN_DQUOTE;
		if (mini->input[*i] == '\"')
			return (create_empty_token(mini, "", state, 2));
	}
	mini->token_type = WORD;
	wrd_len = *i;
	if (flag == 's')
		while (mini->input[*i] && specch(mini->input[*i]) != S_QUOTE)
			(*i)++;
	else if (flag == 'd')
		while (mini->input[*i] && specch(mini->input[*i]) != D_QUOTE)
			(*i)++;
	return (create_token(mini, &mini->input[wrd_len], *state, (*i - wrd_len)));
}

/**
 * @brief Secondary Function for do_lexing_aux.
 * for creation of the token of "".
*/
void	in_special(t_mini *mini, int *i, int *state, int type)
{
	int	wrd_len;

	wrd_len = 0;
	if ((type == R_OUT && specch(mini->input[*i + 1]) == R_OUT)
		|| (type == R_IN && specch(mini->input[*i + 1]) == R_IN))
	{
		if (type == R_OUT)
			mini->token_type = D_R_OUT;
		else
			mini->token_type = HEREDOC;
		create_token(mini, &mini->input[*i], *state, 2);
		(*i)++;
	}
	else if (type == ENV)
	{
		if (mini->input[*i + 1] == '\'' || mini->input[*i + 1] == '\"')
			return ;
		wrd_len = (*i)++;
		while (ft_isalnum(mini->input[*i]))
			(*i)++;
		(*i)--;
		if ((*i - wrd_len) == 0)
			mini->token_type = WORD;
		create_token(mini, &mini->input[wrd_len], *state, (*i - wrd_len + 1));
	}
}
