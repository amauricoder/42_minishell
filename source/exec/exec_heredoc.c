/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 10:54:54 by aconceic          #+#    #+#             */
/*   Updated: 2024/09/04 14:46:03 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	treat_heredocs(t_mini *mini, void *root)
{
	int	pid;
	int	status;

	status = 0;
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid < 0)
		return (err_msg(mini, FORK_ERR, EXIT_FAILURE, 0));
	if (pid == 0)
	{
		g_exit_status = 0;
		update_sig_heredoc();
		open_heredocs(mini, root);
		free_in_execution(mini, EXIT_SUCCESS);
		exit(g_exit_status);
	}
	waitpid(pid, &status, 0);
	signals_init();
	return (status / 256);
}

void	open_heredocs(t_mini *mini, void *root)
{
	t_redir	*nd;

	if (!root)
		return ;
	nd = (t_redir *)root;
	if (nd->type == HEREDOC)
	{
		handle_heredoc(mini, nd);
	}
	else if (nd->type == PIPE)
	{
		open_heredocs(mini, ((t_pipe *)nd)->left);
		open_heredocs(mini, ((t_pipe *)nd)->right);
	}
	if (nd->type == HEREDOC || nd->type == R_IN
		|| nd->type == D_R_OUT || nd->type == R_OUT)
		open_heredocs(mini, nd->down);
}

int	handle_heredoc(t_mini *mini_d, t_redir *hd_node)
{
	hd_node->hd_fd = open(hd_node->hd_tmp, O_CREAT | O_WRONLY | O_TRUNC, 0744);
	while (g_exit_status != 130)
	{
		if (write_on_heredoc(mini_d, hd_node->hd_fd, hd_node))
			break ;
	}
	get_next_line(-3);
	return (close(hd_node->hd_fd));
}

/**
 * @param d main struc
 * @param fd hredoc fd
 * @param nd node
 * @param line user input
 */
int	write_on_heredoc(t_mini *d, int fd, t_redir *nd)
{
	char	*new_line;
	char	*expanded_line;
	char	*line;

	line = readline(">");
	if (!line)
		return (1);
	if (!ft_strncmp(line, nd->fname, ft_strlen(nd->fname))
		&& ft_strlen(line) == ft_strlen(nd->fname))
		return (free(line), 1);
	if (do_hd_expansion(nd, nd->fname))
	{
		new_line = ft_strtrim(line, "\n");
		expanded_line = expand_heredoc(d, new_line);
		if (expanded_line)
		{
			write(fd, expanded_line, ft_strlen(expanded_line));
			free(expanded_line);
		}
	}
	else
		write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
	return (free(line), 0);
}

int	do_hd_expansion(t_redir *node, char *input)
{
	int	i;
	int	s_quotes;
	int	d_quotes;

	i = 0;
	s_quotes = 0;
	d_quotes = 0;
	while (input[i])
	{
		if (input[i] == '\'' && d_quotes % 2 == 0)
			s_quotes++;
		else if (input[i] == '\"')
			d_quotes++;
		i++;
	}
	if (d_quotes || s_quotes || node->hd_ex)
		return (0);
	return (1);
}
