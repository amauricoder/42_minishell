/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 16:02:42 by aconceic          #+#    #+#             */
/*   Updated: 2024/07/08 16:25:42 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * @brief Print the creation of the nodes. 
 * Function used for debugging purposes.
*/
void	print_nodes(t_mini *mini_d)
{
	t_token		*current;
	const char	*str[] = {"GENERAL", "IN_QUOTE", "IN_DQUOTE", "WORD",
		"W_SPACE", "D_QUOTE", "S_QUOTE", "PIPE", "ENV", "RED_OUT",
		"D_R_OUT", "RED_IN", "HEREDOC"};

	current = mini_d->token;
	printf("\n");
	while (current)
	{
		printf("| "YELLOW"Id %3i "RESET" | ", current->id);
		printf(RED"State %10s "RESET" | ", str[current->state]);
		printf(BLUE"Type %7s "RESET" | ", str[current->type + 3]);
		if (current->content != NULL)
			printf(CYAN"Content "RESET"%8s | ", current->content);
		else
			printf(CYAN"Content "RESET"%8s NULL | ", current->content);
		printf(MGT"Length "RESET"%3i |\n", current->len);
		current = current->next;
	}
}

/**
 * @brief just print an array of chars. 
 * Support function to help debbuging
*/
void	printf_matriz(char **to_print)
{
	int	i;

	i = 0;
	if (!to_print)
		return ;
	while (to_print[i])
	{
		printf("printed -> %s |\n", to_print[i]);
		i ++;
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

	if (!str)
		return (NULL);
	dup = malloc(sizeof(char) * qt + 1);
	if (!dup || !qt)
		return (NULL);
	i = 0;
	while (i < qt)
	{
		dup[i] = str[i];
		i ++;
	}
	dup[i] = '\0';
	return (dup);
}

/**
 * @brief Give the error message and set the g_exit_status global variable
 * to the exit value given
 * @return exit_value
*/
int	error_msg_and_exit(char *str, int exit_value)
{
	ft_putendl_fd(str, 2);
	g_exit_status = exit_value;
	return (exit_value);
}
