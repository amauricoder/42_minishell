/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 16:44:37 by aconceic          #+#    #+#             */
/*   Updated: 2024/09/12 16:50:18 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * @brief Exclude "" and '' in cases where they are followed by a letter.
 */
void	exclude_quote_excess(t_mini *d)
{
	int		i;
	int		j;
	char	*new_input;

	new_input = (char *)malloc(strlen(d->input) + 1);
	i = 0;
	j = 0;
	while (i < (int)strlen(d->input))
	{
		if (i > 0 && ft_isalpha(d->input[i - 1]))
		{
			while (i < (int)strlen(d->input)
				&& ((d->input[i] == '\"' && d->input[i + 1] == '\"')
					|| (d->input[i] == '\'' && d->input[i + 1] == '\'')))
			{
				new_input[j++] = ' ';
				i += 2;
			}
		}
		if (i < (int)strlen(d->input))
			new_input[j++] = d->input[i++];
	}
	new_input[j] = '\0';
	ft_strlcpy(d->input, new_input, (int)strlen(d->input) + 1);
	free(new_input);
}

/**
 * @brief Helper function to check if the first word contains invalid characters.
 */
bool	check_first_word_invalid(char *word)
{
	int	i;

	i = 0;
	while (word[i])
	{
		if (word[i] == '\"' || word[i] == '\'')
		{
			i++;
			while (word[i] && (word[i] != '\"' && word[i] != '\''))
				i++;
			if (word[i] == '\0')
				break ;
			i++;
		}
		if (word[i] == '\0' || word[i] == '\"' || word[i] == '\'')
			break ;
		if (word[0] == '|' || word[0] == '<' || word[0] == '>')
			return (true);
		i++;
	}
	return (false);
}

/**
 * @brief Check if the next word in the input is invalid.
 */
int	is_next_word_invalid(char *input)
{
	char	**arr;
	int		result;

	arr = ft_split(input, ' ');
	if (!arr[0])
	{
		free_matriz(arr);
		return (true);
	}
	result = check_first_word_invalid(arr[0]);
	free_matriz(arr);
	return (result);
}
