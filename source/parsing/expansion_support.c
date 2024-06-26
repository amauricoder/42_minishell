/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_support.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismirand <ismirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 19:16:49 by aconceic          #+#    #+#             */
/*   Updated: 2024/06/26 16:00:37 by ismirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Check for how many dollars signs exists in a phrase
 * @return The quantity of dollar signs
*/
int	check_dollar(char *nd_content)
{
	int	i;
	int	qt_dollars;

	if (!nd_content)
		return (0);
	i = 0;
	qt_dollars = 0;
	while (nd_content[i])
	{
		if (nd_content[i] == '$')
			qt_dollars ++;
		i ++;
	}
	return (qt_dollars);
}

/**
 * @brief Check if exists a special char in a word
 * @return If exists, return the sign. If not, return false.
*/
int	have_spacial_char(char *word)
{
	int	i;

	i = 0;
	while (word[i])
	{
		if (specch(word[i]))
			return (word[i]);
		i ++;
	}
	return (false);
}

/**
 * @brief Get the size of a string after the $ until a special char
 * @return The value of the STR after dollarsing. 
*/
int	aftdol_len(char *content)
{
	int		i;
	char	*tmp;

	i = 0;
	if (content[i] == '$')
		i ++;
	while (content[i] && (!specch(content[i + 1]) && content[i + 1]))
		i ++;
	tmp = ft_substr(content, 1, i);
	free(tmp);
	return (i);
}
