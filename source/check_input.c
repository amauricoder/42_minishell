/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismirand <ismirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 09:07:33 by aconceic          #+#    #+#             */
/*   Updated: 2024/06/18 10:27:13 by ismirand         ###   ########.fr       */
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
int	check_input(char *input)
{
	int i;

	i = 0;
	if (!input)
		return (false);
	if (!is_quotes_closed(input) || is_pipe_the_last(input))
		return (error_msg_and_exit("Error\nSyntax error", 2));
	//if (is_redirect_valid(input))	
	//here I need to check for more invalid inputs
	return (false);
}

/**
 * @brief Check if the quotes are closed.
 * @return TRUE if s_quotes and d_quotes are closed
 * 			FALSE if one of them is opened
*/
int is_quotes_closed(char *input)
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

int is_pipe_the_last(char *input)
{
	int	i;

	i = 0;
	while (input[i])
		i ++;
	i --;
	while (i >= 0 && (input[i] == ' ' || input[i] == '\t'))
		i --;
	if (i >= 0 && input[i] == '|')
		return(true);
	return (false);
}
