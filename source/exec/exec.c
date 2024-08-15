/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 16:55:37 by aconceic          #+#    #+#             */
/*   Updated: 2024/08/15 14:08:47 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec_through_tree(t_mini *mini_d, void *root)
{
	int pid;
	int status;
	t_exec	*node_tocheck;

	//Here i need to read the root
	//if the root is exec
	//open child process

	node_tocheck = root;
	if (node_tocheck->type == WORD)
	{
		if (node_tocheck->builtin != 0)
		{
			execute_buildins(mini_d, root);
			printf("executou o builtin");
			return ;
		}
		pid = fork();
		if (pid < 0) 
		{
			error_msg(mini_d, FORK_ERR, 1);
			return;
		} 
		else if (pid == 0) 
		{
			exec_tree(mini_d, root, 1);  // Pass a flag indicating that it's the child
			free_tree(mini_d->root);
			free_and_exit(mini_d);
			exit(0);
		}
		else
		{
		// Parent process: wait for the child
		waitpid(pid, &status, 0);
		mini_d->exit_status = WEXITSTATUS(status);
		}
	}
	else if (node_tocheck->type == R_OUT)
	{
		exec_tree(mini_d, root, 0);
	}
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
