/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 15:44:31 by aconceic          #+#    #+#             */
/*   Updated: 2024/09/03 19:55:37 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief "Filter" cases of redir_in, redir_out e double_redir out.
 * 
 */
int	handle_redir_nodes(t_mini *mini_d, void *root)
{
	t_redir	*node;

	node = root;
	if (mini_d->stdfds[0] == -1 || mini_d->stdfds[1] == -1)
		return (err_msg(mini_d, NULL, 1, 0));
	if (node->type == R_OUT || node->type == D_R_OUT)
	{
		if (exec_redir_out(mini_d, node))
			return (EXIT_FAILURE);
	}
	else if (node->type == R_IN)
	{
		if (exec_redir_in(mini_d, node))
			return (EXIT_FAILURE);
	}
	else if (node->type == HEREDOC)
	{
		if (redirect_heredoc(mini_d, node))
			return (EXIT_FAILURE);
	}
	if (node->down)
		return (do_execution(mini_d, node->down));
	return (EXIT_SUCCESS);
}

/**
 * @brief Do the redirect of fds for the redir_out, taking in consideration
 * if is a R_OUT or D_R_OUT. Also treat the creation of the file using open()
 */
int	exec_redir_out(t_mini *mini_d, t_redir *node)
{
	int	out_fd;

	if (node->type == R_OUT)
		out_fd = open(node->fname, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		out_fd = open(node->fname, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (out_fd < 0)
		return (err_msg(mini_d, NULL, EXIT_FAILURE, 0));
	if (dup2(out_fd, STDOUT_FILENO) == -1)
		return (err_msg(mini_d, NULL, 1, 0));
	close (out_fd);
	return (EXIT_SUCCESS);
}

/**
 * @brief Do the redirect of fds for the redir_in.
 * Also treat the creation of the file using open().
 */
int	exec_redir_in(t_mini *mini_d, t_redir *node)
{
	int	in_fd;

	in_fd = open(node->fname, O_RDONLY);
	if (access(node->fname, R_OK | F_OK) == -1)
		return (err_msg(mini_d, NULL, 1, 0));
	if (in_fd < 0)
		return (err_msg(mini_d, NULL, 1, 0));
	if (dup2(in_fd, STDIN_FILENO) == -1)
	{
		close (in_fd);
		err_msg(mini_d, NULL, 1, 0);
	}
	close (in_fd);
	return (EXIT_SUCCESS);
}
