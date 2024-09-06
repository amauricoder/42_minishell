/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismirand <ismirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 09:07:33 by aconceic          #+#    #+#             */
/*   Updated: 2024/09/06 14:06:13 by ismirand         ###   ########.fr       */
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
int	is_input_invalid(t_mini *mini, char *input)
{
	if (!is_quotes_closed(input) || is_quotes_closed(input) < 0)
	{
		treat_tabs(mini);
		if (!is_quotes_closed(input) || is_redir_invalid(input)
			|| is_pipe_last_or_first(input))
			return (err_msg(mini, SYNTAX_ERR, 2, 0));
	}
	if (is_only_space_or_tab(input))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/**
 * @brief Check if the quotes are closed.
 * @return TRUE if s_quotes and d_quotes are closed
 * 			FALSE if one of them is opened
 * 			-1 if is not in quotes
 * first if / Considera apenas se não estamos dentro de aspas dupla
 * second if / Considera apenas se não estamos dentro de aspas simples
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
		if (input[i] == '\'' && d_quotes % 2 == 0)
			s_quotes++;
		else if (input[i] == '\"' && s_quotes % 2 == 0)
			d_quotes++;
		i++;
	}
	if (!s_quotes && !d_quotes)
		return (-1);
	return (s_quotes % 2 == 0 && d_quotes % 2 == 0);
}

/**
 * @brief Check if the input is only spaces
 * @return true if only space, false for not
 */
int	is_only_space_or_tab(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] != ' ' && input[i] != '	')
			return (false);
		i ++;
	}
	return (true);
}

void	treat_tabs(t_mini *mini)
{
	int		i;

	i = -1;
	while (mini->input[++i])
		if (mini->input[i] == '\t')
			mini->input[i] = ' ';
}
