/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 16:55:37 by aconceic          #+#    #+#             */
/*   Updated: 2024/08/13 16:33:40 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec_tree(t_mini *mini_d, void *root)
{
	int	type;

	type = *((int *)root);
	//printf("This is the type of root \n");
	//printf("%i \n", type);

	//aqui, eu preciso dar fork() e andar a arvore com os processos filhos.

	//se o node for de pipe
		//abrir pipe e fazer redirect
		//chamar a funcao exec_tree(left) p/ executar o node da esquerda 
		//e mandar para o input da direita.
	
	//se o node for de redirect
		//criar o arquivo com o nome do node
		//fazer o redirecionamento de fds de acordo com o tipo de redirect
		//chamar novamente a exec_tree com o proximo node (redirnode->down)
	if (type == R_IN || type == R_OUT || type == D_R_OUT)
		handle_redir_nodes(mini_d, root);
	
	//se o node for de exec
		//Executar o node.
	if (type == WORD)
		execute_cmd(mini_d, root);
	(void)mini_d;
	(void)root;
}
