/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 09:07:33 by aconceic          #+#    #+#             */
/*   Updated: 2024/09/12 17:16:04 by aconceic         ###   ########.fr       */
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
 * @brief Check user input. 1 - if is only space or tab, return EXIT_FAILURE.
 * If quotes are open -> ex ls "this is open' -> Return Err_Msg Syntax Err.
 * If quotes are closed, transform tabs in spaces for outside quotes.
 * Then, copy only the analizable part to a copy str and check for
 * invalid redir OR invalid pipe. 
*/
int	is_input_invalid(t_mini *mini)
{
	int		size;
	char	*to_analize;

	add_history(mini->input);
	if (is_only_space_or_tab(mini->input))
		return (EXIT_FAILURE);
	if (!is_quotes_closed(mini->input))
		return (err_msg(mini, SYNTAX_ERR, 2, 0));
	treat_input_tabs(mini);
	size = get_outquotes_size(mini);
	to_analize = get_outquotes_str(mini, size);
	if (is_redir_invalid(mini->input) || is_pipe_invalid(mini->input))
	{
		free(to_analize);
		return (err_msg(mini, SYNTAX_ERR, 2, 0));
	}
	exclude_quote_excess(mini);
	free(to_analize);
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
	if (s_quotes % 2 == 0 && d_quotes % 2 == 0)
		return (true);
	return (false);
}

/**
 * @brief Check if the input is only spaces or tabs
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

/**
 * @brief Transform tabs in spaces for chars that are outsides "" or ''
 */
void	treat_input_tabs(t_mini *mini)
{
	int		i;
	char	q_type;

	i = 0;
	while (mini->input[i])
	{
		if (mini->input[i] == '\"' || mini->input[i] == '\'')
		{
			q_type = mini->input[i];
			i ++;
			while (mini->input[i] && mini->input[i] != q_type)
				i ++;
		}
		if (mini->input[i] == '\t')
			mini->input[i] = ' ';
		if (mini->input[i] != '\0')
			i ++;
	}
}
