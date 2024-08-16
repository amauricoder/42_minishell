/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 16:55:37 by aconceic          #+#    #+#             */
/*   Updated: 2024/08/16 17:20:15 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	start_execution(t_mini *mini_d, void *root)
{
	int pid;
	int status;
	t_exec	*ndcheck;

	//Here i need to read the root
	//if the root is exec
	//open child process

	if (!root)
		return (error_msg(mini_d, ERR_NO_CMD, 127));
	ndcheck = root;
	//if for pipe
		//abrir a funcao de pipe (redirecionamento dos fds para o paipi)
		//fazer dois fork
		//Em um dos forks start_execution(pipe->left)
		//no outro, o direito start_execution(pipe->right)

	if (ndcheck->type == WORD)
	{
		if (ndcheck->builtin != 0)
			return (execute_buildins(mini_d, root));
		pid = fork();
		if (pid < 0) 
			return (error_msg(mini_d, FORK_ERR, 1));
		else if (pid == 0) 
		{
			exec_tree(mini_d, root, 1);  // Pass a flag inif (access(node->fname, R_OK | F_OK ) == -1)if (access(node->fname, R_OK | F_OK ) == -1)dicating that it's the child
			free_tree(mini_d->root);
			free_and_exit(mini_d);
			exit(0);
		}
		else
		{
			// Parent process: wait for the child
			waitpid(pid, &status, 0);
			mini_d->exit_status = WEXITSTATUS(status);
			//printf("EXIT STATUS %d \n", mini_d->exit_status);
		}
	}
	else if (ndcheck->type == R_OUT || ndcheck->type == R_IN
		|| ndcheck->type == D_R_OUT)
	{
		exec_tree(mini_d, root, 0);
	}
	return (EXIT_SUCCESS);
}

void	exec_tree(t_mini *mini_d, void *root, int is_child)
{
	int type = *((int *)root);

	if (type == R_IN || type == R_OUT || type == D_R_OUT) 
		handle_redir_nodes(mini_d, root);
	if (type == WORD) 
	{
		if (execute_cmd(mini_d, root)) 
		{
			free_tree(mini_d->root);
			free_tokens(mini_d);
			free_main_struct(mini_d);
			if (is_child) {
				exit(127);  // Exit with an error if command is not found
			} else {
				mini_d->exit_status = 127;
			}
		}
	}
}
