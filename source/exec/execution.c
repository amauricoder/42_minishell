/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 16:55:37 by aconceic          #+#    #+#             */
/*   Updated: 2024/08/31 11:58:22 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
//ls > file1 > file2 > file3
int	do_execution(t_mini *mini_d, void *root)
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
		return (EXIT_SUCCESS);
	}
	else if (ndcheck->type == R_OUT || ndcheck->type == R_IN
		|| ndcheck->type == D_R_OUT || ndcheck->type == HEREDOC)
	{
		handle_redir_nodes(mini_d, root);
		return (EXIT_SUCCESS);
	}
	return (EXIT_SUCCESS);
}

int	handle_exec_cmd(t_mini *mini_d, void *root)
{
	int	pid;
	int	status;

	pid = fork();
	status = 0;
	if (pid < 0)
		return (err_msg(mini_d, FORK_ERR, 1, 0));
	else if (pid == 0)
	{
		default_sig();
		if (treat_exec_exception(root))
			exit(free_in_execution(mini_d, 0));
		if (execute_cmd(mini_d, root))
			exit(free_in_execution(mini_d, 127));
	}
	update_signals();
	waitpid(pid, &status, 0);
	set_child_exit(status, mini_d);
	return (mini_d->exit_status);
}
void	set_child_exit(int wstatus, t_mini *mini)
{
	if (WIFSIGNALED(wstatus))
	{
		if (WCOREDUMP(wstatus))
		{
			write(1, "Quit (core dumped)\n", 19);
			mini->exst_printable = 131;
		}
		else if (WTERMSIG(wstatus) == SIGINT)
			mini->exst_printable = 130;
	}
	else
		mini->exst_printable = wstatus / 256;
}