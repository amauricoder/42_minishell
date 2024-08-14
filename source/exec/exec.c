/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 16:55:37 by aconceic          #+#    #+#             */
/*   Updated: 2024/08/14 14:00:35 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec_through_tree(t_mini *mini_d, void *root) 
{
    int pid;
    int status;

    // Fork only at the top level
    pid = fork();
    if (pid < 0) {
        perror("Fork Failed");
        return;
    } else if (pid == 0) {
        // Child process: execute the tree
        exec_tree(mini_d, root, 1);  // Pass a flag indicating that it's the child
        exit(mini_d->exit_status);  // Ensure the child exits properly
    } else {
        // Parent process: wait for the child
        waitpid(pid, &status, 0);
        mini_d->exit_status = WEXITSTATUS(status);
        printf("%d EXIT STATUS \n", mini_d->exit_status);
    }
}

void	exec_tree(t_mini *mini_d, void *root, int is_child) 
{
    int type = *((int *)root);

    if (type == R_IN || type == R_OUT || type == D_R_OUT) {
        handle_redir_nodes(mini_d, root);
    }

    if (type == WORD) {
        if (execute_cmd(mini_d, root) == 1) {
            // Free resources if needed
            free_tree(mini_d->root);
            free_tokens(mini_d);
            free(mini_d->input);
            free(mini_d->prompt);
            free_matriz(mini_d->argv_cp);
            free_env(mini_d->env_d);

            if (is_child) {
                exit(127);  // Exit with an error if command is not found
            } else {
                mini_d->exit_status = 127;
            }
        }
    }
}

/* void	exec_tree(t_mini *mini_d, void *root)
{
	int	type;
	int pid;
	int status;

	type = *((int *)root);
	status = 0;
	//aqui, eu preciso dar fork() e andar a arvore com os processos filhos.
	pid = fork();
	if (pid < 0)
	{
		perror("Fork Failed");
		return ;
	}
	else if (pid == 0) // executado pelo processo filho.
	{
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
			if (execute_cmd(mini_d, root) == 1)
			{
				free_tree(mini_d->root);
				free_tokens(mini_d);
				free(mini_d->input);
				free(mini_d->prompt);
				free_matriz(mini_d->argv_cp);
				free_env(mini_d->env_d);
				exit(127); // 127 is for command not found
			}
	}
	else
	{
		// Código executado pelo processo pai
        // O processo pai espera o término do processo filho
        waitpid(pid, &status, 0);
        // Verifica o status de término do filho, se necessário
        mini_d->exit_status = WEXITSTATUS(status);
		printf("%d EXIT STATUS \n", mini_d->exit_status);
        // Aqui, você pode lidar com o código de saída do processo filho
	}
} */