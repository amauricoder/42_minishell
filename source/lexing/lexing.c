/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:17:04 by aconceic          #+#    #+#             */
/*   Updated: 2024/06/26 14:46:22 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//special (|, >, <,>>,<<, $, ‘ ‘ )
//ft_strchr("|>$<" ,mini_d->input[i])
//tratar erro descentemente
//<< EOF ls -l | cat >output.txt
//a "b c" 'd e' "'f'" '"g"' < | >>
// a "$b c" '$d e'      "'$f'" '"g    h"' < | >>

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
	find_env(mini);
	return (EXIT_SUCCESS);
}

void	do_lexing_aux(t_mini *mini_d, int *i, int *state)
{
	int	type;

	type = specch(mini_d->input[*i]);
	mini_d->token_type = type;
	if (type == S_QUOTE)
		in_quote(mini_d, i, state, 's');
	else if (type == D_QUOTE)
		in_quote(mini_d, i, state, 'd');
	if (type == W_SPACE || type == PIPE || type == ENV
		|| type == R_OUT || type == R_IN)
	{
		if ((type == R_OUT && specch(mini_d->input[*i + 1]) == R_OUT)
			|| (type == R_IN && specch(mini_d->input[*i + 1]) == R_IN)
			|| type == ENV)
			in_special(mini_d, i, state, type);
		else
			create_token(mini_d, &mini_d->input[*i], *state, 1);
		if (*state == GENERAL && type == W_SPACE)
			while (specch(mini_d->input[*i + 1]) == W_SPACE)
				(*i)++;
	}
}

//flag = 's' -> single quote
//flag 'd' -> double quote
void	in_quote(t_mini *mini_d, int *i, int *state, char flag)
{
	int	wrd_len;

	wrd_len = 0;
	(*i)++;
	if (flag == 's')
	{
		*state = IN_QUOTE;
		if (mini_d->input[*i] == '\'')
			return ;
	}
	else if (flag == 'd')
	{
		*state = IN_DQUOTE;
		if (mini_d->input[*i] == '\"')
			return ;
	}
	mini_d->token_type = WORD;
	wrd_len = *i;
	if (flag == 's')
		while (mini_d->input[*i] && specch(mini_d->input[*i]) != S_QUOTE)
			(*i)++;
	else if (flag == 'd')
		while (mini_d->input[*i] && specch(mini_d->input[*i]) != D_QUOTE)
			(*i)++;
	create_token(mini_d, &mini_d->input[wrd_len], *state, (*i - wrd_len));
}

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
