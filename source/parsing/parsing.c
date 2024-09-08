/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:41:52 by aconceic          #+#    #+#             */
/*   Updated: 2024/09/08 20:02:59 by aconceic         ###   ########.fr       */
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

/**
 * @brief Start the creation of the root of the three
 * @param tkn Token
 */
void	*parse_exec(t_mini *mini, t_token *tkn)
{
	t_exec		*exec_node;
	int			id;
	void		*root;

	exec_node = NULL;
	id = 1;
	if (have_command(tkn))
	{
		if (!ft_strncmp(tkn->content, " ", 1) && !tkn->content[1] && tkn->next)
			tkn = tkn->next;
		exec_node = ft_calloc(1, sizeof(t_exec));
		exec_node->id = id;
		id ++;
		exec_node->args = get_cmd(have_command(tkn));
		exec_node->type = WORD;
		if (have_command(tkn) && have_command(tkn)->type == ENV
			&& have_command(tkn)->len == 0)
			exec_node->type = ENV;
		exec_node->builtin = tkn->builtin;
	}
	else
		exec_node = NULL;
	root = exec_node;
	root = parse_redir(mini, tkn, root);
	return (root);
}

void	*parse_redir(t_mini *mini, t_token *token, void *root)
{
	t_token		*last;

	last = get_last_redir(token, 1);
	while (last)
	{
		root = create_redir_node(mini, root, last);
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
