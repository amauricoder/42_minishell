/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismirand <ismirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 16:02:42 by aconceic          #+#    #+#             */
/*   Updated: 2024/06/13 19:51:42 by ismirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void print_nodes(t_mini *mini_d)
{
    t_token *current;
	const char *str[] = {" GENERAL ", "IN_QUOTE ", "IN_DQUOTE", "WORD   ", "W_SPACE",
		"D_QUOTE", "S_QUOTE", "PIPE   ", "ENV    ", "RED_OUT", "D_R_OUT",
		"RED_IN", "HEREDOC"};

	current = mini_d->token;
	printf("\n");
	while (current)
	{
		printf("| "YELLOW"Id %3i "RESET" | ", current->id);
		printf(RED"State %8s "RESET" | ", str[current->state]);
		printf(BLUE"Type %7s "RESET" | ", str[current->type + 3]);
		printf(CYAN"Content "RESET"%8s |\n", current->content);
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
