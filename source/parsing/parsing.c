/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:41:52 by aconceic          #+#    #+#             */
/*   Updated: 2024/07/17 19:55:51 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//Main function that start to build the execution tree.
void *build_tree(t_token *token)
{
	void	*root;

	root = parse_exec(token);
	token = get_last_or_pipe(token);
	if (token)
	{
		//DEbugging purposes
		root = parse_pipe(root, build_tree(token->next)); // Here I need recurtion to construc the right side
		return (root);
	}
	else
		return (root);
}

//Function to start the construction of the tree
void	*parse_exec(t_token *token)
{
	t_exec	*exec_node;
	static int id;
	void	*root;

	exec_node = NULL;
	if (have_command(token))
	{
		exec_node = ft_calloc(1, sizeof(t_exec));
		exec_node->id = id;
		id ++;
		exec_node->args = get_cmd(token);
		exec_node->type = WORD;
	}
	else
		exec_node = NULL;
	root = exec_node;
	root = parse_redir(token, root);
	return (root);
}

void	*parse_redir(t_token *token, void *root)
{
	t_token *last;
	static int id;

	last = get_last_redir(token, 1);
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

void	*parse_pipe(void *left, void *right)
{
	t_pipe *pipe;
	int static id;

	pipe = ft_calloc(1, sizeof(t_pipe));
	pipe->id = id;
	id ++;
	pipe->left = left;
	pipe->right = right;
	pipe->type = PIPE;

	return (pipe);	
}
