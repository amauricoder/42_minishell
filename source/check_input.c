/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 09:07:33 by aconceic          #+#    #+#             */
/*   Updated: 2024/08/14 14:44:59 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * @brief Check if the arguments are valid
 * @return Boolean. Is valid = true. Not valid = 0.
*/
int	is_argument_valid(int argc, char **env)
{
	if (!argc || argc != 1)
	{
		ft_putstr_fd(RED"Try \"./minishell\" instead\n"RESET, 2);
		return (false);
	}
	if (!env)
	{
		ft_putstr_fd(RED"Error\" Undefined ENV\n"RESET, 2);
		return (false);
	}
	return (true);
}

/**
 * @attention syntax error g_exit_status for syntax error = 2;
*/
int	check_input(t_mini *mini, char *input)
{
	if (!input || !is_quotes_closed(input) || is_pipe_last_or_first(input)
		|| is_redir_invalid(input))
		return (error_msg(mini, SYNTAX_ERR, 2));
	return (false);
}

/**
 * @brief Check if the quotes are closed.
 * @return TRUE if s_quotes and d_quotes are closed
 * 			FALSE if one of them is opened
*/
int	is_quotes_closed(char *input)
{
	int	i;
	int	s_quotes;
	int	d_quotes;

	i = 0;
	s_quotes = 0;
	d_quotes = 0;
	while (input[i])
	{
		if (input[i] == '\'' && d_quotes % 2 == 0) // Considera apenas se não estamos dentro de aspas duplas
			s_quotes++;
		else if (input[i] == '\"' && s_quotes % 2 == 0) // Considera apenas se não estamos dentro de aspas simples
			d_quotes++;
		i++;
	}
	return (s_quotes % 2 == 0 && d_quotes % 2 == 0);
}

/**
 * @brief Check if there is a pipe as last characther
*/
int	is_pipe_last_or_first(char *input)
{
	int	i;

	i = 0;
	if (input[0] == '|')
		return (true);
	while (input[i])
		i ++;
	i --;
	while (i >= 0 && (input[i] == ' ' || input[i] == '\t'))
		i --;
	if (i >= 0 && input[i] == '|')
		return (true);
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
		i ++;
	}
	return (is_invalid);
}

/**
 * @brief Check to see if the next word after ">" or ">>"
 * or "<<" or "<" is invalid.
 * @return true if is a invalid word, false otherwise.
 */
int	is_next_word_invalid(char *input)
{
	char	**arr;
	int		i;

	arr = ft_split(input, ' ');
	i = 0;
	if (!arr[0])
	{
		free_matriz(arr);	
		return (true);
	}
	while (arr[0][i])
	{
		if (arr[0][0] == '|' || arr[0][0] == '<' || arr[0][0] == '>')
		{
			free_matriz(arr);
			return (true);
		}
		i ++;
	}
	free_matriz(arr);
	return (false);
}
