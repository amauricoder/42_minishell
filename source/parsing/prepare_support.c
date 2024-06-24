/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_support.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 19:16:49 by aconceic          #+#    #+#             */
/*   Updated: 2024/06/24 15:39:17 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Check for how many dollars signs exists in a phrase
 * @return The quantity of dollar signs
*/
int check_dollar(char *nd_content)
{
	int	i;
	int	qt_dollars;

	if (!nd_content)
		return (0);
	i = 0;
	qt_dollars = 0;
	while(nd_content[i])
	{
		if (nd_content[i] == '$')
			qt_dollars ++;
		i ++;
	}
	return(qt_dollars);
}

/**
 * @brief Check if exists a special char in a word
 * @return If exists, return the sign. If not, return false.
*/
int have_spacial_char(char *word)
{
	int i;

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
 * @brief Check if the the content can be expansive. Example, '$' is not. 
 * '$AM' can be. "$'USER' is not"
 * @return true or false.
*/
int can_be_expansive(char *content)
{
	int i;

	i = 0;
	while(content[i])
	{
		if(content[i] == '$' && specch(content[i + 1]))
			return (false);
		i ++;
	}
	if (i < 2)
		return (false);
	return (true);
}


void printf_dpchar(char **to_print)
{
	int i;

	i = 0;
	if (!to_print)
		return ;
	while(to_print[i])
	{
		printf("printed -> %s |\n", to_print[i]);	
		i ++;
	}
}