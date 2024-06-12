/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismirand <ismirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 15:49:35 by aconceic          #+#    #+#             */
/*   Updated: 2024/06/12 20:56:00 by ismirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_quote(char ch)
{
	if (ch == '\'')
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

int	is_dquote(char ch)
{
	if (ch == '\"')
		return (1);
	else
		return (0);
}

int	is_pipe(char ch)
{
	if (ch == '|')
		return (1);
	else
		return (0);
}

int	is_env(char ch)
{
	if (ch == '$')
		return (1);
	else
		return (0);
}

int	is_redir_in(char ch)
{
	if (ch == '<')
		return (1);
	else
		return (0);
}

int	is_redir_out(char ch)
{
	if (ch == '>')
		return (1);
	else
		return (0);
}

/**
 * @brief Check if the character is a special character
 * @return 1 for yes, 0 for no.
*/
int	special_char(char ch)
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
