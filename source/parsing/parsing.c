/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:41:52 by aconceic          #+#    #+#             */
/*   Updated: 2024/09/03 16:10:28 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//Main function that start to build the execution tree.
void	*do_parsing(t_mini *mini_d, t_token *token)
{
	void	*root;

	root = parse_exec(mini_d, token);
	token = get_last_or_pipe(token);
	if (token)
	{
		root = parse_pipe(root, do_parsing(mini_d, token->next));
		return (root);
	}
	else
		return (root);
}

//Function to start the construction of the tree
void	*parse_exec(t_mini *mini, t_token *token)
{
	t_exec		*exec_node;
	int			id;
	void		*root;

	exec_node = NULL;
	id = 1;
	if (have_command(token))
	{
		if (!ft_strncmp(token->content, " ", 1) && token->next)
			token = token->next;
		exec_node = ft_calloc(1, sizeof(t_exec));
		exec_node->id = id;
		id ++;
		exec_node->args = get_cmd(have_command(token));
		exec_node->type = WORD;
		exec_node->builtin = token->builtin;
	}
	else
		exec_node = NULL;
	root = exec_node;
	root = parse_redir(mini, token, root);
	return (root);
}

void	*parse_redir(t_mini *mini, t_token *token, void *root)
{
	t_token		*last;
	int			id;

	id = 1;
	last = get_last_redir(token, 1);
	while (last)
	{
		root = create_redir_node(mini, root, &id, last);
		last = get_last_redir(last, 0);
		if (!last)
			return (root);
	}
	return (root);
}

void	*parse_pipe(void *left, void *right)
{
	t_pipe		*pipe;
	int			id;

	id = 0;
	pipe = ft_calloc(1, sizeof(t_pipe));
	pipe->id = id;
	id ++;
	pipe->left = left;
	pipe->right = right;
	pipe->type = PIPE;
	return (pipe);
}
