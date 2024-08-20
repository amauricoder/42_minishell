/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 10:54:54 by aconceic          #+#    #+#             */
/*   Updated: 2024/08/20 18:47:23 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/minishell.h"

int		handle_heredoc(t_mini *mini_d, void *root)
{
	t_redir *hd_node;
	char	*line;
	int		hd_fd;

	hd_node = root;
	hd_fd = open("/tmp/heredoc.tmp", O_CREAT | O_WRONLY | O_TRUNC, 0744);
	if (hd_fd < 0)
		err_msg(mini_d, NULL, EXIT_FAILURE, 0);
	while(1)
	{
		write(STDOUT_FILENO, "> ", 2);
		line = get_next_line(mini_d->stdfds[0]);
		if (!line)
			break;
		if (!ft_strncmp(line, hd_node->fname, ft_strlen(hd_node->fname))
			&& ft_strlen(line) - 1 == ft_strlen(hd_node->fname))
			break;
		write(hd_fd, line, ft_strlen(line));
		free(line);
	}
	get_next_line(-3);
	close(hd_fd);
	if (line)
		free(line);
	redirect_heredoc(mini_d);
	if (hd_node->down)
		do_execution(mini_d, hd_node->down);
	unlink("/tmp/heredoc.tmp");
	return (EXIT_SUCCESS);
}

int	redirect_heredoc(t_mini *mini_d)
{
	int	tmp_fd;
	
	tmp_fd = open("/tmp/heredoc.tmp", O_RDONLY);
	if (tmp_fd == -1)
		return (err_msg(mini_d, NULL, EXIT_FAILURE, 0));
	if (dup2(tmp_fd, STDIN_FILENO) == -1)
	{
		close(tmp_fd);
		return (err_msg(mini_d, NULL, EXIT_FAILURE, 0));	
	}
	close(tmp_fd);
	return(EXIT_SUCCESS);
}
