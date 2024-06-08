/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 16:02:42 by aconceic          #+#    #+#             */
/*   Updated: 2024/06/08 16:13:54 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void print_nodes(t_mini *mini_d)
{
    t_token *current;

	current = mini_d->token;
	while (current)
	{
		printf("token id %i | ", current->id);
		printf("token state %i | ", current->state);
		printf("token type %i | ", current->type);
		printf("token content %s \n", current->content);
		current = current->next;
	}
}

//treat error here
/**
 * @brief Make the duplication of a word for a specific qt of characters
 * @attention TREAT ERROR DECENTLY
*/
char	*ft_strdup_qt(char *str, int qt)
{
	char	*dup;
	int		i;
	
	dup = malloc(sizeof(char) * qt + 1);
	if (!dup || !qt)
		return (NULL);
	i = 0;
	while(i < qt)
	{
		dup[i] = str[i]; 
		i ++;
	}
	dup[i] = '\0';
	return (dup);
}