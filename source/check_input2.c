/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 16:23:23 by aconceic          #+#    #+#             */
/*   Updated: 2024/09/09 12:13:45 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

/**
 * @attention Support function to is_input_invalid()
 * @brief Get the size of the input outside quotes and d_quotes.
 * Example: I will take this size, "Not this one", But this one also.
 * Will return the value of ->I will the this size, , But this one also.
 */
int	get_outquotes_size(t_mini	*mini)
{
	int		i;
	int		size;
	char	q_type;

	i = 0;
	size = 0;
	while (mini->input[i])
	{
		if (mini->input[i] == '"' || mini->input[i] == '\'')
		{
			q_type = mini->input[i];
			i ++;
			while (mini->input[i] && mini->input[i] != q_type)
				i ++;
		}
		size ++;
		if (mini->input[i] != '\0')
			i ++;
	}
	return (size);
}

/**
 * @attention Support function to is_input_invalid();
 * @brief Gets the input outside quotes and d_quotes.
 * 
 */
char	*get_outquotes_str(t_mini	*mini, int size)
{
	int		i;
	int		j;
	char	*to_analize;
	char	q_type;

	i = 0;
	j = 0;
	to_analize = ft_calloc(sizeof(char), (size + 1));
	while (mini->input[i])
	{
		if (mini->input[i] == '\"' || mini->input[i] == '\'')
		{
			q_type = mini->input[i ++];
			while (mini->input[i] && mini->input[i] != q_type)
				i ++;
			if (mini->input[i] == q_type)
				i ++;
		}
		if (mini->input[i] == '\'' || mini->input[i] == '\"')
			continue ;
		to_analize[j ++] = mini->input[i];
		if (mini->input[i] != '\0')
			i ++;
	}
	return (to_analize);
}
