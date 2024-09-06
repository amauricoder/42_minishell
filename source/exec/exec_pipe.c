/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismirand <ismirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 11:22:05 by aconceic          #+#    #+#             */
/*   Updated: 2024/09/06 15:34:51 by ismirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	handle_pipe(t_mini *mini_d, void *root)
{
	int		p_fd[2];
	int		pid[2];
	int		status[2];

	signals_pipe();
	if (pipe(p_fd) == -1)
		return (err_msg(mini_d, "pipe failed", EXIT_FAILURE, false));
	pid[0] = fork();
	if (pid[0] == -1)
		return (err_msg(mini_d, "fork failed", EXIT_FAILURE, false));
	if (pid[0] == 0)
	{
		treat_pipe_child(mini_d, root, p_fd, true);
		exit(EXIT_SUCCESS);
	}
	pid[1] = fork();
	if (pid[1] == -1)
		return (err_msg(mini_d, "fork failed", EXIT_FAILURE, false));
	if (pid[1] == 0)
	{
		treat_pipe_child(mini_d, root, p_fd, false);
		exit(EXIT_SUCCESS);
	}
	return (end_handle_pipe(mini_d, p_fd, pid, status));
}

int	exec_pipe(t_mini *mini_d, void *root, int p_fd[2], int is_left)
{
	t_pipe	*pipe_nd;

	pipe_nd = root;
	signals_child();
	if (is_left)
	{
		if (dup2(p_fd[1], STDOUT_FILENO) == -1)
			err_msg(mini_d, "dup2 failed", EXIT_FAILURE, false);
		close(p_fd[0]);
		close(p_fd[1]);
		do_execution(mini_d, pipe_nd->left);
		free_in_execution(mini_d, EXIT_SUCCESS);
		exit(EXIT_SUCCESS);
	}
	if (dup2(p_fd[0], STDIN_FILENO) == -1)
		err_msg(mini_d, "dup2 failed", EXIT_FAILURE, false);
	close(p_fd[1]);
	close(p_fd[0]);
	do_execution(mini_d, pipe_nd->right);
	exit(free_in_execution(mini_d, mini_d->exst_printable));
}

int	end_handle_pipe( t_mini *mini, int p_fd[2], int pid[2], int status[2])
{
	close(p_fd[0]);
	close(p_fd[1]);
	waitpid(pid[0], &status[0], 0);
	waitpid(pid[1], &status[1], 0);
	if (WIFEXITED(status[1]))
		mini->exst_printable = WEXITSTATUS(status[1]);
	if (status[1] / 256 == 130 || status[0] / 256 == 130)
		printf("\n");
	return (EXIT_SUCCESS);
}

int	treat_pipe_child(t_mini *mini, void	*root, int p_fd[2], int is_left)
{
	if (is_left)
	{
		close(p_fd[0]);
		exec_pipe(mini, root, p_fd, is_left);
		close(p_fd[1]);
		return (EXIT_SUCCESS);
	}
	close(p_fd[1]);
	exec_pipe(mini, root, p_fd, false);
	close(p_fd[0]);
	return (EXIT_SUCCESS);
}
