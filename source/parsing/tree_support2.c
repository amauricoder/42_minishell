/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_support2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:58:41 by aconceic          #+#    #+#             */
/*   Updated: 2024/07/19 10:46:13 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Goes to the last node or the next Pipe.
 * If goes to the last one, this will return NULL pointer.
 * If find a token->type == PIPE, this will return the PIPE token.
*/
t_token	*get_last_or_pipe(t_token *to_advance)
{
	while (to_advance)
	{
		if (to_advance->type == PIPE)
			return (to_advance);
		to_advance = to_advance->next;
	}
	return (NULL);
}

/**
 * @warning Support function for parse_exec();
 */
char	**get_cmd(t_token *token)
{
	t_token	*current;
	char	**args;
	int		i;

	current = token;
	args = NULL;
	i = get_qt_cmd_tokens(token);
	if (i == 0)
		return (NULL);
	args = ft_calloc(i + 1, sizeof(char *));
	i = -1;
	while (current && current->type != PIPE)
	{
		if (current->type == WORD || current->type == ENV)
			args[++ i] = ft_strdup(current->content);
		current = current->next;
	}
	return (args);
}

/**
 * @warning Support function to parse_redir();
 * @brief Get the last REDIR_NODE in a command line in the first interaction.
 * if is not the first interaction, will get the REDIR_NODE before.
 * This function works withing a loop in parse_redir()
 */
t_token	*get_last_redir(t_token *node, int first_interaction)
{
	t_token	*last;

	if (!node)
		return (NULL);
	last = node;
	if (first_interaction)
	{
		while (last->next && last->type != PIPE)
		{
			last->next->prev = last;
			last = last->next;
		}
		last = last->prev;
	}
	else
	{
		if (last->type == R_IN || last->type == R_OUT
			|| last->type == D_R_OUT || last->type == HEREDOC)
			last = last->prev;
	}
	while (last && last->type != PIPE)
	{
		if (last->type == R_IN || last->type == R_OUT
			|| last->type == D_R_OUT || last->type == HEREDOC)
			return (last);
		last = last->prev;
	}
	return (NULL);
}
