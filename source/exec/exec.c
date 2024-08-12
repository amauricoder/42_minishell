/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 16:55:37 by aconceic          #+#    #+#             */
/*   Updated: 2024/08/10 17:13:43 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec_tree(t_mini *mini_d, void *root)
{
	//aqui, eu preciso dar fork() e andar a arvore com os processos filhos.
	//se o node for de pipe
		//chamar a funcao exec_tree() p/ executar o node da esquerda e mandar para o input da direita.
	//se o node for de redirect
		//criar o arquivo com o nome do node
		//fazer o redirecionamento de fds de acordo com o tipo de redirect
		//chamar novamente a exec_tree com o proximo node (redirnode->down)
	//se o node for de exec
		//Executar o node.
	(void)mini_d;
	(void)root;
}

void	redir_exec_tree(t_mini *mini_d, void *root)
{
	//abrir o arquivo com o nome do node
	int	fd;
	int	type;

	type = *((int *)root);
	printf("This is the type of root \n");
	printf("%i \n", type);
	(void)fd;
	(void)mini_d;
}