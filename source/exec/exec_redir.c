/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismirand <ismirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 15:44:31 by aconceic          #+#    #+#             */
/*   Updated: 2024/08/14 14:55:14 by ismirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_redir_nodes(t_mini *mini_d, void *root)
{
	t_redir *node;
	int		stdout_backup;
	int		stdin_backup;

	node = root;
	stdout_backup = dup(STDOUT_FILENO);
	stdin_backup = dup(STDIN_FILENO);
	if (node->type == R_OUT || node->type == D_R_OUT)
		exec_redir_out(mini_d, node);
	else if (node->type == R_IN)
		exec_redir_in(mini_d, node);
	if (dup2(stdout_backup, STDOUT_FILENO) == -1
		|| dup2(stdin_backup, STDIN_FILENO) == -1)
		error_msg(mini_d, "Minishell: Error redir exec", 1);
	close(stdout_backup);
	close(stdin_backup);
}

//Redir out sem arquivo cria um
//D_REDIR_OUT e REDIR_OUT tem functionalidades diferentes
//DOUBLE -> APPEND
//REDIR IN -> TRUNCA (TRUCO LADRAO)
void	exec_redir_out(t_mini *mini_d, t_redir *node)
{
	int	out_fd;

	if (node->type == R_OUT)
		out_fd = open(node->fname, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		out_fd = open(node->fname, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (out_fd < 0)
		error_msg(mini_d, "Minishell: Error redir out", 1);

	if (dup2(out_fd, STDOUT_FILENO) == -1)
		error_msg(mini_d, "Minishell: Error Redir Out fd", 1);
	close (out_fd);
	if (node->down)
		exec_tree(mini_d, node->down, 1);
}

//APENAS LE O ARQUIVO
//SE NAO HOUVER -> ERRO
//NAO ESQUECER PERMISSOES
void	exec_redir_in(t_mini *mini_d, t_redir *node)
{
	int	in_fd;

	in_fd = open(node->fname, O_RDONLY);
	if (access(node->fname, R_OK | F_OK ) == -1)
	{
		error_msg(mini_d, "Minishell: No such file or directory", 1);
		//Clean everything from this point
		exit(1);
		return ;
	}
	if (in_fd == -1)
		error_msg(mini_d, "Minishell: Error exec redir in", 1);
	if (dup2(in_fd, STDIN_FILENO) == -1)
		error_msg(mini_d, "Minishell: Error exec redir in", 1);
	close (in_fd);
	if (node->down)
		exec_tree(mini_d, node->down, 1);
	//for testing purposes
	//execlp("cat", "cat", NULL);
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