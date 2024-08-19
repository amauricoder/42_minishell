/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_support.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:18:44 by aconceic          #+#    #+#             */
/*   Updated: 2024/08/19 16:40:57 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Checks if there is a possible command in the nodes.
 * ex. wc -> this is a node->type = WORD || $USER -> this is a node->type = ENV
 * Both can be possible commands.
 */
int	have_command(t_token *node)
{
	t_token	*current;

	current = node;
	while (current)
	{
		if (current->type == WORD || current->type == ENV)
			return (true);
		current = current->next;
	}
	return (false);
}

/**
 * @attention Support function to parsing/parsing.c  -> parse_redir() function.
 * @brief Function to alloc and create the redir_node.
 * @param down Ptr to a possible exec or redir node, defined on parse_redir().
 * @param id Id for future debug possibilities
 * @param node token node that we will get the name of the file.  
 */
t_redir	*create_redir_node(void *down, int id, t_token *node)
{
	t_redir	*redir;

	redir = ft_calloc(1, sizeof(t_redir));
	redir->id = id;
	id ++;
	redir->fname = get_redir_name(node);
	redir->len = ft_strlen(redir->fname);
	redir->down = down;
	redir->type = node->type;
	return (redir);
}

/**
 * @attention Support function to create_redir_node().
 * @brief This function get the redirection node content.
 * ex. cmd > file1 --- This will get the file1 and return this.
 * @warning Possible problems with edge cases. Need to test the cases
 * UPDATE -> We updated this in a form that will never go into INVALID.
 * But this will stay due to debud.
 */
char	*get_redir_name(t_token *node)
{
	t_token	*current;

	current = node;
	if (current->next)
	{
		while (current && current->type != FILE_NAME)
			current = current->next;
	}
	if (current->type != FILE_NAME)
		return (ft_strdup("INVALID"));
	else
		return (ft_strdup(current->content));
}

/**
 * @warning Support function to parsing/parsing.c get_cmd().
 * @brief Get the quantity of word tokens until the NULL or '|' char.
 */
int	get_qt_cmd_tokens(t_token *token)
{
	t_token	*current;
	int		i;

	i = 0;
	current = token;
	while (current && current->type != PIPE)
	{
		if (current->type == WORD || current->type == ENV)
			i ++;
		current = current->next;
	}
	return (i);
}
