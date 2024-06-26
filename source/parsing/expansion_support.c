/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_support.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 19:16:49 by aconceic          #+#    #+#             */
/*   Updated: 2024/06/26 11:46:52 by aconceic         ###   ########.fr       */
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

void	clean_tokens(t_mini *mini_d, int kind)
{
	t_token	*head;

	while (mini_d->token == NULL)
		mini_d->token = mini_d->token->next;
	head = mini_d->token;
	(void)kind;
}
