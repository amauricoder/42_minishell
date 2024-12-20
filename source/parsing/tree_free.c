/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:55:52 by aconceic          #+#    #+#             */
/*   Updated: 2024/09/04 15:52:17 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_exec(void *root)
{
	t_exec	*exec;

	exec = (t_exec *)root;
	free_matriz(exec->args);
	free(exec);
}

void	free_redir(void *root)
{
	t_redir	*redir;

	redir = (t_redir *)root;
	if (redir->hd_tmp)
		free(redir->hd_tmp);
	if (redir->hd_fd != -1)
		close(redir->hd_fd);
	free_tree(redir->down);
	free(redir->fname);
	free(redir);
}

void	free_pipe(void *root)
{
	t_pipe	*pipe;

	pipe = (t_pipe *)root;
	free_tree(pipe->left);
	free_tree(pipe->right);
	free(pipe);
}

// Recursive function to free the tree
void	free_tree(void *root)
{
	int	type;

	if (!root)
		return ;
	type = *((int *)root);
	if (type == WORD || type == ENV)
		free_exec(root);
	else if (type == R_IN || type == R_OUT
		|| type == D_R_OUT || type == HEREDOC)
		free_redir(root);
	else if (type == PIPE)
		free_pipe(root);
}
