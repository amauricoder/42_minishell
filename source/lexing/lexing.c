/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:17:04 by aconceic          #+#    #+#             */
/*   Updated: 2024/06/25 20:27:08 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//special (|, >, <,>>,<<, $, ‘ ‘ )
//ft_strchr("|>$<" ,mini_d->input[i])
//tratar erro descentemente
//<< EOF ls -l | cat >output.txt
//a "b c" 'd e' "'f'" '"g"' < | >>
// a "$b c" '$d e'      "'$f'" '"g    h"' < | >>
static void	find_env(t_mini *mini_d);

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

static void	find_env(t_mini *mini_d)
{
	t_token *head;

	head = mini_d->token;
	while (mini_d->token)
	{
		if (mini_d->token->type == WORD && mini_d->token->state != IN_QUOTE
			&& mini_d->token->content[0] == '$' 
			&& ft_isalnum(mini_d->token->content[1]))
			mini_d->token->type = ENV;
		mini_d->token = mini_d->token->next;
	}
	mini_d->token = head;
}

void	do_lexing_aux(t_mini *mini_d, int *i, int *state)
{
	int	type;
	int	wrd_len;

	wrd_len = 0;
	type = specch(mini_d->input[*i]);
	mini_d->token_type = type;
	if (type == D_QUOTE)
	{
		(*i)++;
		if (mini_d->input[*i] == '\"')
			return ;
		*state = IN_DQUOTE;
		mini_d->token_type = WORD;
		wrd_len = *i;
		while (mini_d->input[*i] && specch(mini_d->input[*i]) != D_QUOTE)
			(*i)++;
		//printf("%i\n", *i);
		create_token(mini_d, &mini_d->input[wrd_len], *state, (*i - wrd_len));
	}
	else if (type == S_QUOTE)
	{
		(*i)++;
		*state = IN_QUOTE;
		if (mini_d->input[*i] == '\'')
			return ;
		mini_d->token_type = WORD;
		wrd_len = *i;
		while (mini_d->input[*i] && specch(mini_d->input[*i]) != S_QUOTE)
			(*i)++;
		create_token(mini_d, &mini_d->input[wrd_len], *state, (*i - wrd_len));
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
		else if (type == ENV)
		{
			if (mini_d->input[*i + 1] == '\'' || mini_d->input[*i + 1] == '\"')
				return ;
			wrd_len = *i;
			(*i)++;
			while (ft_isalnum(mini_d->input[*i]))
				(*i)++;
			(*i)--;
 			if ((*i - wrd_len) == 0)
				mini_d->token_type = WORD;
			create_token(mini_d, &mini_d->input[wrd_len], *state, (*i - wrd_len + 1));
		}
		else
			create_token(mini_d, &mini_d->input[*i], *state, 1);
		if (*state == GENERAL && type == W_SPACE)
		{
			while (specch(mini_d->input[*i]) == W_SPACE)
				(*i)++;
			(*i)--;
		}
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
/* int	define_state(char ch, int state, int *i)
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
} */
