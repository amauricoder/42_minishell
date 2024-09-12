/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 16:23:23 by aconceic          #+#    #+#             */
/*   Updated: 2024/09/12 20:50:23 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * @brief Check if there is a pipe as last characther
 * Return TRUE for invalid (YES! IS INVALID)
 * and FALSE for valid(NO, IS NOT INVALID).
*/
int	is_pipe_invalid(char *input)
{
	int	i;

	i = ft_strlen(input) - 1;
	if (input[0] == '|' || input[i] == '|')
		return (true);
	while (i >= 0 && (input[i] == ' ' || input[i] == '\t'))
		i--;
	if (i >= 0 && input[i] == '|' && !is_quoted(input, &i))
		return (true);
	if (is_pipe_invalid_aux(input))
		return (true);
	return (false);
}

/**
 * @brief Check this situation ls |   | wc
 * This is syntax error. Return TRUE for invalid (YES! IS INVALID)
 *  and FALSE for valid(NO, IS NOT INVALID).
 */
int	is_pipe_invalid_aux(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (!is_quoted(input, &i))
		{
			if (input[i] == '|')
			{
				i ++;
				while (input[i] == ' ' || input[i] == '\t')
					i ++;
				if (input[i] == '|')
					return (true);
				continue ;
			}
		}
		i++;
	}
	return (false);
}

/**
 * @brief Check to see if the redir have a name after.
 * Example - << EOF is a valid redir. Only << is invalid.
 * @return true or value indicating that is invalid, false otherwise.
 */
int	is_redir_invalid(char *inpt)
{
	int	i;
	int	is_invalid;

	i = 0;
	is_invalid = 0;
	while (inpt[i])
	{
		if (!is_quoted(inpt, &i))
			if (is_redir_invalid_aux(inpt, i, &is_invalid))
				return (true);
		i ++;
	}
	return (is_invalid);
}

int	is_redir_invalid_aux(char *inpt, int i, int *is_invalid)
{
	if (!ft_strncmp(&inpt[i], ">>", 2) || !ft_strncmp(&inpt[i], "<<", 2))
	{
		if (inpt[i + 2])
			is_invalid += is_next_word_invalid(&inpt[i + 2]);
		else
			return (true);
	}
	else if (!ft_strncmp(&inpt[i], ">", 1) || !ft_strncmp(&inpt[i], "<", 1))
	{
		if (inpt[i + 1])
			is_invalid += is_next_word_invalid(&inpt[i + 1]);
		else
			return (true);
	}
	return (false);
}

/**
 * @brief Ignore blocks of str inside "" and ''
 * return false when the block end, return true if not
*/
int	is_quoted(char *input, int *i)
{
	int	is_invalid;
	int	in_single_quote;
	int	in_double_quote;

	is_invalid = 0;
	in_single_quote = 0;
	in_double_quote = 0;
	while (input[*i])
	{
		if (input[*i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		if (input[*i] == '"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		if (!in_single_quote && !in_double_quote)
			return (false);
		(*i)++;
	}
	return (true);
}
