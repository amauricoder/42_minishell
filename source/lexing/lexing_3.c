/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 15:49:35 by aconceic          #+#    #+#             */
/*   Updated: 2024/06/08 16:12:57 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

int	is_dquote(char ch)
{
	if (ch == '\"')
		return (1);
	else
		return (0);
}

/**
 * @brief Check if the character is a special character
 * @return 1 for yes, 0 for no.
*/
int	is_special_char(char ch)
{
	if(ch == '\'' || ch == '\"' || ch == '<' || ch == '>' || ch == '|'
		|| ch == '$' || is_space(ch) || ch == '\n' || ch == '\0')
	{	
		return (true);
	}
	return (false);
}