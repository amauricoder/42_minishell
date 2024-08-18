/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 15:44:31 by aconceic          #+#    #+#             */
/*   Updated: 2024/08/18 18:08:30 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief "Filter" cases of redir_in, redir_out e double_redir out.
 * 
 */
void	handle_redir_nodes(t_mini *mini_d, void *root)
{
	t_redir	*node;

	node = root;
	if (mini_d->stdfds[0] == -1 || mini_d->stdfds[1] == -1)
    {
        perror("dup failed");
        err_msg(mini_d, "Error redir exec", 1, 0);
        return;
    }
	if (node->type == R_OUT || node->type == D_R_OUT)
		exec_redir_out(mini_d, node);
	else if (node->type == R_IN)
		exec_redir_in(mini_d, node);
	if (node->down)
		start_execution(mini_d, node->down);
}

/**
 * @brief Do the redirect of fds for the redir_out, taking in consideration
 * if is a R_OUT or D_R_OUT. Also treat the creation of the file using open()
 */
void	exec_redir_out(t_mini *mini_d, t_redir *node)
{
	int	out_fd;

	if (node->type == R_OUT)
		out_fd = open(node->fname, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		out_fd = open(node->fname, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (out_fd < 0)
		err_msg(mini_d, "Error redir out", 1, 0);
	if (dup2(out_fd, STDOUT_FILENO) == -1)
		err_msg(mini_d, "Error Redir Out fd", 1, 0);
	close (out_fd);
}

/**
 * @brief Do the redirect of fds for the redir_in.
 * Also treat the creation of the file using open().
 */
void	exec_redir_in(t_mini *mini_d, t_redir *node)
{
	int	in_fd;

	in_fd = open(node->fname, O_RDONLY);
	if (access(node->fname, R_OK | F_OK) == -1)
	{
		err_msg(mini_d, NULL, 1, 0);
		return ;
	}
	if (in_fd < 0)
		err_msg(mini_d, NULL, 1, 0);
	if (dup2(in_fd, STDIN_FILENO) == -1)
		err_msg(mini_d, NULL, 1, 0);
	close (in_fd);
}
/* Redirecionamento de Saída (>)

O redirecionamento > cria um arquivo novo ou sobrescreve um arquivo existente. Para replicar esse comportamento com open(), você deve usar as seguintes flags:

    O_WRONLY: Abre o arquivo para escrita.
    O_CREAT: Cria o arquivo se ele não existir.
    O_TRUNC: Trunca (esvazia) o arquivo para zero bytes se ele já existir.

Redirecionamento de Saída com Append (>>)

O redirecionamento >> anexa ao final de um arquivo existente ou cria um novo arquivo se ele não existir. Para replicar esse comportamento, você deve usar:

    O_WRONLY: Abre o arquivo para escrita.
    O_CREAT: Cria o arquivo se ele não existir.
    O_APPEND: Adiciona dados ao final do arquivo, sem truncá-lo. */