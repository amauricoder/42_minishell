/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:41:52 by aconceic          #+#    #+#             */
/*   Updated: 2024/07/16 18:42:28 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//Main function that start to build the execution tree.
int build_tree(t_mini *mini_d)
{
	void	*root;

	root = parse_exec(mini_d);
	//if tem |
		//parse PIPE
	print_tree(root, "", 0);
	return (EXIT_SUCCESS);
}

//Function to start the construction of the tree
void	*parse_exec(t_mini *mini_d)
{
	t_exec	*exec_node;
	t_token	*node;
	static int id;
	void	*root;

	node = mini_d->token;
	exec_node = NULL;
	if (have_command(node))
	{
		exec_node = ft_calloc(1, sizeof(t_exec)); //free this
		exec_node->id = id;
		id ++;
		exec_node->args = get_cmd(node);
		exec_node->type = WORD;
	}
	else
		exec_node = NULL;
	root = exec_node;
	root = parse_redir(mini_d, root);
	return (root);
}

void	*parse_redir(t_mini *mini_d, void *root)
{
	t_token *last;
	static int id;

	last = get_last_redir(mini_d->token, 1);
	//criar um node de redirect
	//fazer com que ele aponte para o node de exec ou de redirect
	while (last)
	{
		root = create_redir_node(root, id, last); //here allocate memory
		id ++;
		last = get_last_redir(last, 0);
		if(!last)
			return (root);
	}
	return (root);
}

/**
 * @warning Support function for parse_exec();
 */
char	**get_cmd(t_token *token)
{
	t_token *current;
	char **args;
	int		i;

	current = token;
	args = NULL;
	i = get_qt_cmd_tokens(token);
	if (i == 0)
		return (NULL);
	args = ft_calloc(i + 1, sizeof(char *)); //free this
	i = -1;
	while (current && current->type != PIPE)
	{
		if (current->type == WORD || current->type == ENV)
			args[++ i] = ft_strdup(current->content);//free this
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
t_token *get_last_redir(t_token *node, int first_interaction)
{
	t_token *last;

	last = node;
	if (first_interaction)
	{
		while (last->next && last->type != PIPE)
			last = last->next;
	}
	else
	{
		if (last->type == R_IN || last->type == R_OUT 
				|| last->type == D_R_OUT)
			last = last->prev;
	}
	while (last)
		{
			if (last->type == R_IN || last->type == R_OUT 
				|| last->type == D_R_OUT)
			return (last);
			last = last->prev;
		}
	return (NULL);
}

