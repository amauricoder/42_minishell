/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 14:20:26 by aconceic          #+#    #+#             */
/*   Updated: 2024/08/18 19:22:10 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	handle_pipe(t_mini *mini_d, void *root)
{
	int		p_fd[2];
	int		pid1;
	int		pid2;

	if (pipe(p_fd) == -1)
		return (err_msg(mini_d, "pipe failed", EXIT_FAILURE, false));
	pid1 = fork();
	if (pid1 == -1)
		return (err_msg(mini_d, "fork failed", EXIT_FAILURE, false));
	if (pid1 == 0) // Child process 1
		exec_pipe(mini_d, root, p_fd, true);
	pid2 = fork();
	if (pid2 == -1)
		return (err_msg(mini_d, "fork failed", EXIT_FAILURE, false));
	if (pid2 == 0) // Child process 2
		exec_pipe(mini_d, root, p_fd, false);
	// Parent process closes both ends of the pipe
	close(p_fd[0]);
	close(p_fd[1]);
	// Wait for both child processes to finish
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);

	return (EXIT_SUCCESS);
}

int	exec_pipe(t_mini *mini_d, void *root, int p_fd[2], int is_left)
{
	t_pipe	*pipe_nd;

	pipe_nd = root;
	if (is_left)
	{
		// Replace stdout with the write end of the pipe
		if (dup2(p_fd[1], STDOUT_FILENO) == -1)
			err_msg(mini_d, "dup2 failed", EXIT_FAILURE, false);
		close(p_fd[0]); // Close the read end of the pipe
		close(p_fd[1]); // Close the original write end of the pipe
		start_execution(mini_d, pipe_nd->left);
		free_in_execution(mini_d, EXIT_SUCCESS);
		exit(EXIT_SUCCESS); // Exit child process
	}
	if (dup2(p_fd[0], STDIN_FILENO) == -1)
		err_msg(mini_d, "dup2 failed", EXIT_FAILURE, false);
	close(p_fd[1]); // Close the write end of the pipe
	close(p_fd[0]); // Close the original read end of the pipe
	start_execution(mini_d, pipe_nd->right);
	free_in_execution(mini_d, EXIT_SUCCESS);
	exit(EXIT_SUCCESS); // Exit child process
}
	