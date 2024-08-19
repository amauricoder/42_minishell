/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 16:55:37 by aconceic          #+#    #+#             */
/*   Updated: 2024/08/19 15:28:04 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
//ls > file1 > file2 > file3
int	start_execution(t_mini *mini_d, void *root)
{
	t_exec	*ndcheck;

	if (!root)
		return (err_msg(mini_d, NO_CMD, 127, 0));
	ndcheck = root;
	if (ndcheck->type == PIPE)
		return (handle_pipe(mini_d, root));
	if (ndcheck->type == WORD)
	{
		if (ndcheck->builtin != 0)
			return (execute_buildins(mini_d, root));
		handle_exec_cmd(mini_d, root);
	}
	else if (ndcheck->type == R_OUT || ndcheck->type == R_IN
		|| ndcheck->type == D_R_OUT)
		handle_redir_nodes(mini_d, root);
	return (EXIT_SUCCESS);
}

int	handle_exec_cmd(t_mini *mini_d, void *root)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid < 0)
		return (err_msg(mini_d, FORK_ERR, 1, 0));
	else if (pid == 0)
	{
		if (execute_cmd(mini_d, root))
			exit(free_in_execution(mini_d, 127));
	}
	waitpid(pid, &status, 0);
	mini_d->exit_status = WEXITSTATUS(status);
	return (mini_d->exit_status);
}
